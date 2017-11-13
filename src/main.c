#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#include "graphing.h"

int main(int argc, char *argv[])
{
    if (argc == 3) {
        if (strcmp(argv[2], "cos") == 0) {
            generate_plot_script("cos(x)"); 
            return generate_points(argv[1], "cos(x)");
        } else if (strcmp(argv[2], "sin") == 0) {
            generate_plot_script("sin(x)");
            return generate_points(argv[1], "sin(x)");
        } else {
            error("Please enter what type of graph you wish to draw");
            return EXIT_FAILURE;
        }
    } else if (argc == 2) {
        error("Please enter what type of graph you wish to draw");
        return EXIT_FAILURE;
    } else {
        error("Please enter port to Arduino");
        return EXIT_FAILURE; 
    }
}
