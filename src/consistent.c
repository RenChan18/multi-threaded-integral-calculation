// consistent.c
#include "consistent.h"

double function_to_integrate(double x) {
    return (pow(x, 2) + pow(M_E, x))/(pow(x, 3) + 3 * pow(M_E, x));  
}


double calculate_integral_trapezoidal(double (*func)(double), double lower_limit, double upper_limit, int num_intervals) {
    double interval_width = fabs(upper_limit - lower_limit) / num_intervals;
    double sum_midpoints = 0.0;
    for (int i = 1; i < num_intervals; i++) {
        double x = lower_limit + i * interval_width;
        sum_midpoints += func(x);
    }
    double integral = (interval_width / 2) * (func(lower_limit) + func(upper_limit) + 2 * sum_midpoints);
    return integral;
}


void perform_integration(splits) {
    double lower_limit, upper_limit, tolerance;
    int num_intervals = 2;  


    printf("\nEnter the initial limit: ");
    scanf("%lf", &lower_limit);
    printf("\nEnter the: final limit: ");
    scanf("%lf", &upper_limit);
    printf("\nEnter the desired accuracy: ");
    scanf("%lf", &tolerance);


    double current_integral = calculate_integral_trapezoidal(function_to_integrate, lower_limit, upper_limit, num_intervals);
    double previous_integral;


    do {
        previous_integral = current_integral;
        num_intervals++;
        current_integral = calculate_integral_trapezoidal(function_to_integrate, lower_limit, upper_limit, num_intervals);
    } while (fabs(current_integral - previous_integral) >= tolerance);


    printf("The integral is: %lf\n", current_integral);
    printf("Calculated with %d intervals\n", num_intervals);
}

