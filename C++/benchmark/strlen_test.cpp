// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <benchmark/benchmark.h>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <random>
#include <sstream>
#include <set>
#include <algorithm>

// c++17 version
int generate_str(int size, std::string* str) {
    str->clear();
    std::string char_list{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    // assert(char_list.length() == 26 * 2);
    std::sample(char_list.begin(), char_list.end(), std::back_inserter(*str), size,
                std::mt19937(std::random_device()()));
    return 0;
}

// faster than c++17 sample realization
// maybe sample not deplacated elements
int generate_str_c11(int size, std::string* str) {
    str->clear();
    std::string char_list{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    // assert(char_list.length() == 26 * 2);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, char_list.length() - 1);
    std::ostringstream ostr;
    for (int i = 0; i < size; ++i) {
        ostr << char_list[dis(gen)];
    }
    *str = ostr.str();
    return 0;

}

// almost same speed as std::sample
int generate_str_c11_uniq(int size, std::string* str) {
    std::set<int> res;
    str->clear();
    std::string char_list{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    // assert(char_list.length() == 26 * 2);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, char_list.length() - 1);
    std::ostringstream ostr;
    while (res.size() < size) {
        int idx = dis(gen);
        if (res.find(idx) == res.end()) {
            ostr << char_list[idx];
            res.insert(idx);
        }
    }
    *str = ostr.str();
    return 0;

}

static void bench_generate_str(benchmark::State &state) {
    while (state.KeepRunning()) {
        std::string out_str;
        generate_str(10, &out_str);
    }
}
BENCHMARK(bench_generate_str);

static void bench_generate_str2(benchmark::State &state) {
    while (state.KeepRunning()) {
        std::string out_str;
        generate_str_c11(10, &out_str);
    }
}
BENCHMARK(bench_generate_str2);

static void bench_generate_str3(benchmark::State &state) {
    while (state.KeepRunning()) {
        std::string out_str;
        generate_str_c11_uniq(10, &out_str);
    }
}
BENCHMARK(bench_generate_str3);

int strlen_new(const char* str, int prev_len) {
    return str[0] == '\0' ? prev_len :
           str[1] == '\0' ? prev_len + 1 :
           str[2] == '\0' ? prev_len + 2 :
           str[3] == '\0' ? prev_len + 3 :
           str[4] == '\0' ? prev_len + 4 :
           str[5] == '\0' ? prev_len + 5 :
           str[6] == '\0' ? prev_len + 6 :
           str[7] == '\0' ? prev_len + 7 :
           strlen_new(str + 8, prev_len + 8);
}

static void bench_strlen(benchmark::State &state) {
    std::string out_str;
    generate_str_c11(1000, &out_str);
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(strlen(out_str.c_str()));
    }
}
BENCHMARK(bench_strlen);

// slow a lot
static void bench_strlen_new(benchmark::State &state) {
    std::string out_str;
    generate_str_c11(1000, &out_str);
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(strlen_new(out_str.c_str(), 0));
    }
}
BENCHMARK(bench_strlen_new);

BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
