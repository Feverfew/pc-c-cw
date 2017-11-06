#include <math.h>
#include <stdio.h>

/*! \brief Maps a number from one range to another
 *
 * \param x Number to map
 * \param in_min Minimum value in initial range.
 * \param in_max Maximum value in initial range.
 * \param out_min Minimum value in new range.
 * \param out_max Maximum value in new range.
 * \return Return The mapped value.
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
