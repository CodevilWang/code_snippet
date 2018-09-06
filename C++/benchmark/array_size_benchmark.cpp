// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <benchmark/benchmark.h>
#include <vector>
#include <type_traits>
static void bench_extent(benchmark::State &state) {
    int a[10];
    while (state.KeepRunning()) {
        int b = 0;
        benchmark::DoNotOptimize(b += std::extent<decltype(a)>::value);
    }
}
BENCHMARK(bench_extent);

template<typename T, std::size_t N>
constexpr std::size_t lengthof2(T(&)[N]) {
    return N;
}

static void bench_lengthof(benchmark::State &state) {
    int a[10];
    while (state.KeepRunning()) {
        int b = 0;
        benchmark::DoNotOptimize(b += lengthof2(a));
    }
}
BENCHMARK(bench_lengthof);

BENCHMARK_MAIN();
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
