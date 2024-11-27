// consostent.h
#ifndef CONSISTENT_H
#define CONSISTENT_H

#include <stdio.h>
#include <stdlib.h>


double calculate_integral_trapezoidal(double (*func)(double), double lower_limit, double upper_limit, int num_intervals);
void perform_integration(int initial_intervals, double (*func)(double));

#endif // CONSISTENT_H
