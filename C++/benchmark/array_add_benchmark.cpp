// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <benchmark/benchmark.h>
static const int N = 10000;
static const int M = 10000;

static void bench_row_major(benchmark::State &state) {
    int** data = new int*[M];
    for (int i = 0; i < M; ++i) {
        data[i] = new int[N];
        memset(data[i], 0, N * sizeof(int));
    }
    while (state.KeepRunning()) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] += 10;
            }
        }
    }
}
BENCHMARK(bench_row_major);

static void bench_column_major(benchmark::State &state) {
    int** data = new int*[M];
    for (int i = 0; i < M; ++i) {
        data[i] = new int[N];
        memset(data[i], 0, N * sizeof(int));
    }
    while (state.KeepRunning()) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                data[j][i] += 10;
            }
        }
    }
}
BENCHMARK(bench_column_major);


BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */