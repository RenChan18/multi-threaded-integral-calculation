// parallel.h

#ifndef PARALLEL_H
#define PARALLEL_H
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 4

typedef struct {
    double (*func)(double);
    double lower_limit;
    double upper_limit;
    int num_intervals;
    int thread_id;
    double partial_sum;
} TD2;

double calculate_integral_trapezoidal_segment(double (*func)(double), double lower_limit, double upper_limit, int num_intervals);
void* thread_func_p(void* arg);

void parallel(int initial_intervals, double (*func)(double));

#endif // PARALLEL_H
