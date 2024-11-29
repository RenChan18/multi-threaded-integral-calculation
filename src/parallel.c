// parallel.c
#include "parallel.h"
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
double global_sum = 0.0;
void* thread_func_p(void* arg) {
    TD2* data = (TD2*)arg;

    double interval_width = (data->upper_limit - data->lower_limit) / data->num_intervals;
    int start = data->thread_id * (data->num_intervals / NUM_THREADS);
    int end = start + (data->num_intervals / NUM_THREADS);

    double local_sum = 0.0;
    for (int i = start; i < end; i++) {
        double x = data->lower_limit + i * interval_width;
        local_sum += data->func(x);
    }

    pthread_mutex_lock(&mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

double calculate_integral_parallel_sum(double (*func)(double), double lower_limit, double upper_limit, int num_intervals) {
    pthread_t threads[NUM_THREADS];
    TD2 thread_data[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].func = func;
        thread_data[i].lower_limit = lower_limit;
        thread_data[i].upper_limit = upper_limit;
        thread_data[i].num_intervals = num_intervals;
        thread_data[i].thread_id = i;

        pthread_create(&threads[i], NULL, thread_func_p, (void*)&thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double interval_width = (upper_limit - lower_limit) / num_intervals;
    double integral = (interval_width / 2) * (func(lower_limit) + func(upper_limit) + 2 * global_sum);
    return integral;
}

void parallel(int initial_intervals, double (*func)(double)) {
    double lower_limit, upper_limit;
     printf("\nEnter the initial limit: ");
    scanf("%lf", &lower_limit);
    printf("\nEnter the final limit: ");
    scanf("%lf", &upper_limit);
    double integral = calculate_integral_parallel_sum(func, lower_limit, upper_limit, initial_intervals);
    printf("The integral is: %lf\n", integral);

}

