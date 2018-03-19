// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <benchmark/benchmark.h>
#include <unordered_map>
static void bench_unordered_map_find(benchmark::State &state) {
    std::vector<int> key_list;
    std::unordered_map<int, int> v;
    int total_elements = 1000000;
    for (int i = 0; i < total_elements; ++i) {
        v.insert(std::make_pair(i, i));
    }
    while (state.KeepRunning()) {
        uint64_t sum = 0;
        for (const std::pair<int, int>& it : v) {
            sum += it.second;
        }

    }
}
BENCHMARK(bench_unordered_map_find);
static void bench_unordered_map_find2(benchmark::State &state) {
    std::vector<int> key_list;
    std::unordered_map<int, int> v;
    int total_elements = 1000000;
    for (int i = 0; i < total_elements; ++i) {
        v.insert(std::make_pair(i, i));
    }
    while (state.KeepRunning()) {
        uint64_t sum = 0;
        for (const auto& it : v) {
            sum += it.second;
        }
    }
}
BENCHMARK(bench_unordered_map_find2);

BENCHMARK_MAIN();
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
