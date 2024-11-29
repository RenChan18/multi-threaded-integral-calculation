// consostent.h
#ifndef CONSISTENT_H
#define CONSISTENT_H

//#include "read_data.h"
#define TOLERANCE 1e-6
#include <stdio.h>
#include <math.h>


void read_input1(double* lower_limit, double* upper_limit);
double calculate_integral_trapezoidal(double (*func)(double), double lower_limit, double upper_limit, int num_intervals);
void perform_integration(int initial_intervals, double (*func)(double));

#endif // CONSISTENT_H
