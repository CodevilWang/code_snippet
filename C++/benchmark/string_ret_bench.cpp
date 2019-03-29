// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <benchmark/benchmark.h>
#include <string>
static const int CHAR_LEN = 100000;
void work(std::string* out_str) {
    for (int i = 0; i < CHAR_LEN; ++i) {
        *out_str += 'i';
    }
    return;
}
std::string work2() {
    std::string str;
    for (int i = 0; i < CHAR_LEN; ++i) {
        str += 'i';
    }
    return str;
}

class TmpC {
public:
    std::string str;
    std::string&& work3() {
        str.clear();
        for (int i = 0; i < CHAR_LEN; ++i) {
            str += 'i';
        }
        return std::move(str);
    }
    std::string work4() {
        str.clear();
        for (int i = 0; i < CHAR_LEN; ++i) {
            str += 'i';
        }
        return str; 
    }
};

static void bench_work_str_pointer(benchmark::State &state) {
    while (state.KeepRunning()) {
        std::string a;
        work(&a);
    }
}
BENCHMARK(bench_work_str_pointer);

static void bench_work_str(benchmark::State &state) {
    while (state.KeepRunning()) {
        std::string ret = work2();
    }
}
BENCHMARK(bench_work_str);

static void bench_work_str_rv(benchmark::State &state) {
    TmpC c;
    while (state.KeepRunning()) {
        std::string ret = c.work3();
    }
}
BENCHMARK(bench_work_str_rv);

static void bench_work_str_rv2(benchmark::State &state) {
    TmpC c;
    while (state.KeepRunning()) {
        std::string ret = c.work4();
    }
}
BENCHMARK(bench_work_str_rv2);


BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
