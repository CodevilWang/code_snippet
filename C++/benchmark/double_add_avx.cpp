// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
//
#include <benchmark/benchmark.h>
#include <immintrin.h>
#include <vector>
#include <random>
static const size_t total_num = 1000000;
static float in_data0[total_num];
static float in_data1[total_num];
static float out_data[total_num];
void plain_add(float* const in_data_0, float* const in_data_1, int size, float* out) {
    for (int i = 0; i < size; ++i) {
        out[i] = in_data_0[i] + in_data_1[i];    
    }
}
static void bench_avx_float_add(benchmark::State &state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 10000000.0);
    auto gener = [&dis, &gen] {
        return dis(gen);
    };
    std::generate_n(in_data0, total_num, gener);
    std::generate_n(in_data1, total_num, gener);
    while (state.KeepRunning()) {
        static const int width = sizeof(__m256d) / sizeof(float);
        int remainer = total_num & (width - 1);
        for (int i = 0; i < total_num - remainer; i += width) {
            __m256d a_res = _mm256_add_pd(_mm256_load_ps(in_data0 + i), _mm256_load_ps(in_data1 + i));
            _mm256_storeu_ps(out_data + i, a_res);
            // _m256_store_ps(, );
        }
        plain_add(in_data0 + total_num - remainer, in_data1 + total_num - remainer, remainer, out_data + total_num - remainer);
    }
}
BENCHMARK(bench_avx_float_add);

static void bench_float_add(benchmark::State &state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 10000000.0);
    auto gener = [&dis, &gen] {
        return dis(gen);
    };
    std::generate_n(in_data0, total_num, gener);
    std::generate_n(in_data1, total_num, gener);
    while (state.KeepRunning()) {
        plain_add(in_data0, in_data1, total_num, out_data);
    }
}
BENCHMARK(bench_float_add);

BENCHMARK_MAIN();
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
