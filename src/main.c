#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "graphing.h"

int main(int argc, char *argv[])
{
    if (argc == 2) {
        generate_plot_script("cos(x)"); 
        generate_points(argv[1]);
    } else {
        error("Please enter port to Arduino");
        return EXIT_FAILURE; 
    }
    return EXIT_SUCCESS;
}
