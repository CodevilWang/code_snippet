// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <assert.h>
#include <random>
#include <benchmark/benchmark.h>
#include <omp.h>

static const size_t ADD_NUM = 1000000;
using dre = std::default_random_engine;
static void bench_add_random(benchmark::State& state) {
    while (state.KeepRunning()) {
        for (int j = 0; j < 4; ++j) {
            static uint64_t random_seed = time(NULL);
            dre random_engine;
            random_engine.seed(random_seed);
            uint64_t res = 0;
            for (size_t i = 0; i < ADD_NUM; ++i) {
                res += random_engine();
                if (res > std::numeric_limits<uint32_t>::max()) {
                    res = 0;
                }
            }
            // assert(res >= 0);
            printf("%llu\n", res);
        }
    }
    // printf("%llu\n", res);
}
BENCHMARK(bench_add_random);
static void bench_add_random_openmp(benchmark::State& state) {
    while (state.KeepRunning()) {
        #pragma omp parallel for
        for (int j = 0; j < 4; ++j) {
            // printf("thread num %d total thread %d\n", omp_get_thread_num(), omp_get_num_threads());
            static uint64_t random_seed = time(NULL);
            dre random_engine;
            random_engine.seed(random_seed);
            uint64_t res = 0;
            for (size_t i = 0; i < ADD_NUM; ++i) {
                res += random_engine();
                if (res > std::numeric_limits<uint32_t>::max()) {
                    res = 0;
                }
            }
            // assert(res >= 0);
            printf("%llu\n", res);
        }
    }
    // printf("%llu\n", res);
}
BENCHMARK(bench_add_random_openmp);

BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
