#ifndef GRAPHING_H
#define GRAPHING_H value


double map(double x, double in_min, double in_max, double out_min, double out_max);
void calc_coords(double r, double prev_coords[], int data_val);
void error(char* msg);
int generate_points(char* port_loc);
void generate_plot_script(char* func_to_draw);

#endif /* ifndef GRAPHING_H */
