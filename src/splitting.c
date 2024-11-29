// splitting.c

#include "splitting.h"

void read_input(double* lower_limit, double* upper_limit) {
    printf("\nEnter the initial limit: ");
    scanf("%lf", lower_limit);
    printf("\nEnter the final limit: ");
    scanf("%lf", upper_limit);
}


double calculate_integral_segment(double (*func)(double), double lower, double upper, int intervals_per_segment) {
    double interval_width = (upper - lower) / intervals_per_segment;
    double sum = 0.0;

    for (int i = 1; i < intervals_per_segment; i++) {
        double x = lower + i * interval_width;
        sum += func(x);
    }

    double integral = (interval_width / 2) * (func(lower) + func(upper) + 2 * sum);
    return integral;
}

void* thread_func(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    double segment_width = (data->upper_limit - data->lower_limit) / data->num_threads;
    double local_lower = data->lower_limit + data->thread_id * segment_width;
    double local_upper = local_lower + segment_width;

    data->result = calculate_integral_segment(data->func, local_lower, local_upper, data->total_intervals / data->num_threads);

    pthread_exit(NULL);
}

void calculate_integral_trapezoidal_split(double (*func)(double), double lower_limit, double upper_limit, double tolerance, int initial_intervals, int num_threads) {
    int total_intervals = initial_intervals > 0 ? initial_intervals : 2;
    double current_integral = 0.0, previous_integral;

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].func = func;
        thread_data[i].lower_limit = lower_limit;
        thread_data[i].upper_limit = upper_limit;
        thread_data[i].total_intervals = total_intervals;
        thread_data[i].num_threads = num_threads;
        thread_data[i].thread_id = i;

        pthread_create(&threads[i], NULL, thread_func, (void*)&thread_data[i]);
    }


    double sum = 0.0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        sum += thread_data[i].result;
    }

    current_integral = sum;


    do {
        previous_integral = current_integral;
        total_intervals *= 2; 

      
        for (int i = 0; i < num_threads; i++) {
            thread_data[i].total_intervals = total_intervals;
            pthread_create(&threads[i], NULL, thread_func, (void*)&thread_data[i]);
        }

     
        sum = 0.0;
        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
            sum += thread_data[i].result;
        }

        current_integral = sum;
    } while (fabs(current_integral - previous_integral) >= tolerance);

    printf("The integral is: %lf\n", current_integral);
    printf("Calculated with %d intervals\n", total_intervals);
}



void init_threads(int initial_intervals, double (*func)(double))
{
    double lower_limit, upper_limit;
    int num_intervals = initial_intervals > 0 ? initial_intervals : 2;
    read_input(&lower_limit, &upper_limit);

    calculate_integral_trapezoidal_split(func, lower_limit, upper_limit, TOLERANCE, initial_intervals, NUM_THREADS);

}

