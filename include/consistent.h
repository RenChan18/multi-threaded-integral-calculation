// consostent.h
#ifndef CONSISTENT_H
#define CONSISTENT_H
#define _USE_MATH_DEFINES 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double function_to_integrate(double x);
double calculate_integral_trapezoidal(double (*func)(double), double lower_limit, double upper_limit, int num_intervals);
void perform_integration(double splits);

#endif // CONSISTENT_H
