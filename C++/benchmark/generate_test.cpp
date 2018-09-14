// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <random>
#include <benchmark/benchmark.h>
inline int g_rand() {
    return 10;
    // return rand() % 100;
}
static void bench_generate(benchmark::State &state) {
    std::vector<int> v;
    v.resize(1000000);
    while (state.KeepRunning()) {
        std::generate(v.begin(), v.end(), g_rand);
    }
    float data[100000];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis{0.0, 10000000.0};
    auto gener = [&dis, &gen](){
               return dis(gen);
    };
    std::generate_n(data, 100000, gener);
    for (int i = 0; i < 10; ++i) {
        printf("%f\n", data[i]);
    }
}
BENCHMARK(bench_generate);

static void bench_raw_fill(benchmark::State &state) {
    std::vector<int> v;
    v.resize(1000000);
    while (state.KeepRunning()) {
        for (int i = 0; i < 1000000; ++i) {
            v[i] = 10;
        }
    }
}
BENCHMARK(bench_raw_fill);

BENCHMARK_MAIN();
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
