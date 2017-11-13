#ifndef GRAPHING_H
#define GRAPHING_H value

void error(char msg[]);
double map(double x, double in_min, double in_max, double out_min, double out_max);
void calc_coords(double r, double prev_coords[], int data_val);
char* calc_led_colour(double coords[], char func_to_draw[]);
int generate_points(char port_loc[], char func_to_draw[]);
void generate_plot_script(char func_to_draw[]);

#endif /* ifndef GRAPHING_H */
