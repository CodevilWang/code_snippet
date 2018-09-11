// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <omp.h>
static long num_steps = 100000;
double step;
#define NUM_THREADS 4
int main() {
    int i;
    double pi;
    double start_time;
    double end_time;
    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    double sum = 0.0;
    #pragma omp parallel reduction(+:sum) private(i)
    {
        double x = 0.0;
        int id = omp_get_thread_num();
        for (i = id; i < num_steps; i+= NUM_THREADS) {
            x = (i - 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    }
    pi += sum * step;
    // for (i = 0, pi = 0.0; i < NUM_THREADS; ++i) {
    //     pi += sum[i] * step;
    // }
    end_time = omp_get_wtime();
    printf("Pi = %f\n Running time %f\n", pi, end_time - start_time);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
