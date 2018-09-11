// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <omp.h>

int main() {
    int x = 2;
    #pragma omp parallel num_threads(2) shared(x)
    {
        if (omp_get_thread_num() == 0) {
            x = 5;
        } else {
            printf("1:Thread# %d: x = %d\n", omp_get_thread_num(), x);
        }
        #pragma omp barrier
        if (omp_get_thread_num() == 0) {
            printf("2:Thread# %d:x=%d\n", omp_get_thread_num(), x);
        } else {
            printf("3:Thread# %d:x=%d\n", omp_get_thread_num(), x);
        }
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
