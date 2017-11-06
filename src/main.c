#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "graphing.h"
#include "arduino-serial-lib.h"

#define BUF_MAX 1024
#define BAUDRATE 9600
#define TIMEOUT 5000
#define EOLCHAR '\n'

void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        FILE *gnuplot_data;
        gnuplot_data = fopen("data.dat", "w+");
        int data_value;
        double prev_coords[2] = {0};
        char buffer[BUF_MAX];
        int fd = -1;
        fd = serialport_init(argv[1], BAUDRATE);
        if (fd == -1) {
            error("Serial port not opened");
            return EXIT_FAILURE; 
        }
        serialport_flush(fd);

        while(prev_coords[0] <= 2*M_PI) {
            memset(buffer, 0, BUF_MAX);
            serialport_read_until(fd, buffer, EOLCHAR, BUF_MAX, TIMEOUT);
            int data_val = strtol(buffer, NULL, 10);
            calc_coords(0.1, prev_coords, data_val);
            fprintf(gnuplot_data, "%lf %lf\n", prev_coords[0], prev_coords[1]);
            fflush(stdout);
        }
        fclose(gnuplot_data);
    } else {
        error("Please enter port to Arduino");
        return EXIT_FAILURE; 
    }
    return EXIT_SUCCESS;
}
