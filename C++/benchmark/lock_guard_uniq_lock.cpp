// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <benchmark/benchmark.h>
#include <vector>
#include <mutex>
static void lock_guard_bench(benchmark::State &state) {
    std::mutex m;
    int a = 0;
    while (state.KeepRunning()) {
        std::lock_guard<std::mutex> ul(m);
        benchmark::DoNotOptimize(a = 10);
    }
}
BENCHMARK(lock_guard_bench)->Threads(4);

static void unique_lock_bench(benchmark::State &state) {
    std::mutex m;
    int a = 0;
    while (state.KeepRunning()) {
        std::unique_lock<std::mutex> ul(m);
        benchmark::DoNotOptimize(a = 10);
    }
}
BENCHMARK(unique_lock_bench)->Threads(4);

BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
