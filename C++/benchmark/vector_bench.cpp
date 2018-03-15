// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <benchmark/benchmark.h>
#include <vector>
static void bench_push_back(benchmark::State &state) {
    while (state.KeepRunning()) {
        std::vector<int> v;
        v.push_back(42);
    }
}
BENCHMARK(bench_push_back);
BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
