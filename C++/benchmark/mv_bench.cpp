// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <benchmark/benchmark.h>
#include <stdio.h>
#include <vector>

static constexpr uint32_t VALUE_SIZE = 10000000;
class DataItem {
public:
    DataItem() {
        _value.resize(VALUE_SIZE, 100);
    }
    DataItem(const std::vector<uint32_t>& others) {
        _value = others;
    }
    DataItem(std::vector<uint32_t>&& others) {
        _value = others;
    }
private:
    std::vector<uint32_t> _value;
};
static void bench_mv(benchmark::State &state) {
    std::vector<uint32_t> data = std::vector<uint32_t>(VALUE_SIZE, 100);
    while (state.KeepRunning()) {
        DataItem d(data);
    }
}
BENCHMARK(bench_mv);

static void bench_copy(benchmark::State &state) {
    std::vector<uint32_t> data = std::vector<uint32_t>(VALUE_SIZE, 100);
    while (state.KeepRunning()) {
        DataItem d(std::move(data));
    }
}
BENCHMARK(bench_copy);


BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
