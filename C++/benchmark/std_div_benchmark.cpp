// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <benchmark/benchmark.h>
#include <cstdlib>

static void bench_stddiv(benchmark::State &state) {
    std::div_t a;
    while (state.KeepRunning()) {
        int i = 100123;
        int j = 3221;
        a = std::div(i, j);
        benchmark::DoNotOptimize(a);
    }
    printf("1\t%d\t%d\n", a.quot, a.rem); 
}
BENCHMARK(bench_stddiv);

static void bench_div(benchmark::State &state) {
    int a = 0;
    int b = 0;
    while (state.KeepRunning()) {
        int i = 100123;
        int j = 3221;
        a = i / j;
        b = i % j;
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);
    }
    printf("2\t%d\t%d\n", a, b);
}
BENCHMARK(bench_div);


BENCHMARK_MAIN();
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
