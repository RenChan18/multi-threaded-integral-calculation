// splitting.h
#ifndef SPLITTING_H
#define SPLITTING_H

#define TOLERANCE 1e-6
#define NUM_THREADS 4
#include <pthread.h>
//#include "read_data.h"
#include <stdio.h>
#include <math.h>



typedef struct {
    double (*func)(double);
    double lower_limit;    
    double upper_limit;    
    int total_intervals;   
    int num_threads;       
    double result;         
    int thread_id;         
} ThreadData;

void read_input(double* lower_limit, double* upper_limit);
void init_threads(int initial_intervals, double (*func)(double));
void calculate_integral_trapezoidal_split(double (*func)(double), double lower_limit, double upper_limit, double tolerance, int initial_intervals, int num_threads);
double calculate_integral_segment(double (*func)(double), double lower, double upper, int intervals_per_segment);
void* thread_func(void* arg);

#endif // SPLITTING_H
