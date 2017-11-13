#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "arduino-serial-lib.h"

/*! \brief Displays an error message to the user
 *
 * \param msg Message to display to the user
 */
void error(char msg[])
{
    fprintf(stderr, "%s\n",msg);
}

/*! \brief Maps a number from one range to another
 *
 * \param x Number to map
 * \param in_min Minimum value in initial range.
 * \param in_max Maximum value in initial range.
 * \param out_min Minimum value in new range.
 * \param out_max Maximum value in new range.
 * \return The mapped value.
 */
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;  
}

/*! \brief Calculates next coordinates to plot
 *
 *  Calculates next coordinates to plot using polar coordinates, using the
 *  previous coordinates as the centre, with a given modulus and using the 
 *  analog value read from the potentiometer as the argument.
 *
 * \param r Modulus
 * \param prev_coords Coordinates in the form {x, y} of the previous plot.
 * \param data_val Analog value given by the potentiometer.
 */
void calc_coords(double r, double prev_coords[], int data_val)
{
    double arg = map((double) data_val, 0, 1023, (double) -M_PI/2, (double) M_PI/2);
    prev_coords[0] += r*cos(arg);
    prev_coords[1] += r*sin(arg);
}
/*! \brief Determines what colour the LED on the Arduino should be.
 *
 *  Finds the residue between the graph that the user has drawn with the
 *  function they are attempting to draw and sends back a string which will
 *  be used to lght up the Arduino LED as appropriate, with green (g) being
 *  fairly good, yellow (y) being ok and red (r) indicating a poor performance.
 *
 * \param coords Last coordinate in the form {x, y} that the user has drawn.
 * \param func_to_draw The function that the user is attempting to draw. 
 * \return Colour that the LED should be
 */
char* calc_led_colour(double coords[], char func_to_draw[]){
    double func_value = 0;
    if (strcmp(func_to_draw, "cos(x)") == 0) {
        func_value = cos(coords[0]);
    } else {
        func_value = sin(coords[0]);
    }

    if (fabs(func_value - coords[1]) < 0.05) {
        return "g";
    } else if (fabs(func_value - coords[1]) < 0.3) {
        return "y";
    } else {
        return "r";
    }
}

/*! \brief Generate points and save them to a file
 *
 *  Opens a file for writing. the calc_coords() function will calculate each
 *  subsequent based on the value of the potentiometer. Each subsequent 
 *  iteration will be saved to file.
 *
 * \param port_loc The location of the arduino on the file system
 * \param fund_to_draw The function the user is trying to draw
 * \return Exit success or failure depending on if the port is opened
 */
int generate_points(char port_loc[], char func_to_draw[])
{
    const int buf_max = 1024;
    const int baudrate = 9600;
    const int timeout = 5000;
    const char eolchar = '\n';
    int fd = -1; // Serial port file descriptor
    // Attempt to open connection with arduino
    int rc;
    fd = serialport_init(port_loc, baudrate);
    if (fd == -1) {
        error("Serial port not opened");
        return EXIT_FAILURE; 
    }
    FILE *gnuplot_data;
    gnuplot_data = fopen("data.dat", "w+");
    int start_y = 0;
    if (strcmp(func_to_draw, "cos(x)") == 0) {
        start_y = 1;
    }
    double prev_coords[2] = {0, start_y};
    int data_val;
    char buffer[buf_max];
    serialport_flush(fd);
    // Generate points and save to file
    while(prev_coords[0] <= 2*M_PI) {
        memset(buffer, 0, buf_max);
        serialport_read_until(fd, buffer, eolchar, buf_max, timeout);
        data_val = strtol(buffer, NULL, 10);
        calc_coords(0.005, prev_coords, data_val);
        fprintf(gnuplot_data, "%lf %lf\n", prev_coords[0], prev_coords[1]);
        fflush(gnuplot_data);
        // Set LED colour based on residue
        rc = serialport_write(fd, calc_led_colour(prev_coords, func_to_draw));
        if (rc == -1) {
            error("Error writing to arduino");
        }
    }
    fclose(gnuplot_data);
    return EXIT_SUCCESS;
}

/*! \brief Generates the gnuplot script.
 *
 *  Generates a script that will later on be run by the gunplot program
 *
 * \param func_to_draw The name of the function that the user will try to draw
 */
void generate_plot_script(char func_to_draw[])
{
    FILE *gnuplot_script;
    gnuplot_script = fopen("liveplot.gnu", "w+");
    fprintf(gnuplot_script, "set xrange[0:6.3]\n"
                            "set yrange[-2:2]\n"
                            "plot \"data.dat\" with lines, %s\n"
                            "pause 0.01\n"
                            "reread\n", func_to_draw);
    fflush(gnuplot_script);
    fclose(gnuplot_script);
}

