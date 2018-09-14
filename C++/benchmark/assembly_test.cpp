// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <immintrin.h>
#include <random>
#include <algorithm>
static const size_t total_num = 1000000;
static float in_data0[total_num];
static float in_data1[total_num];
static float out_data[total_num];
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 10000000.0);
    auto gener = [&dis, &gen] {
        return dis(gen);
    };
    std::generate_n(in_data0, total_num, gener);
    std::generate_n(in_data1, total_num, gener);
#ifndef __USE_AVX__
    for (int i = 0; i < total_num; ++i) {
        out_data[i] = in_data0[i] + in_data1[i];    
    }
#else
    static const int width = sizeof(__m256d) / sizeof(float);
    for (int i = 0; i < total_num; i += width) {
        __m256d a_res = _mm256_add_pd(_mm256_load_ps(in_data0 + i), _mm256_load_ps(in_data1 + i));
        _mm256_storeu_ps(out_data + i, a_res);
        // _m256_store_ps(, );
    }
#endif
    printf("%f\n", out_data[0]);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
