// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <benchmark/benchmark.h>
#include <pthread.h>
#include <vector>
#include <atomic>
static void multithread_inc_pthread(benchmark::State &state) {
    static uint64_t res = 0;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    if (state.thread_index == 0) {
        res = 0;
    }
    for (auto _: state) {
        for (int i = 0; i < 1000000; ++i) {
            pthread_mutex_lock(&mutex);
            ++res;
            pthread_mutex_unlock(&mutex);
        }
    }
    if (state.thread_index == 0) {
        assert(res > 100000);
    }
}
BENCHMARK(multithread_inc_pthread)->Threads(4);

static void singlethread_inc(benchmark::State &state) {
    static uint64_t res = 0;
    for (auto _: state) {
        for (int i = 0; i < 1000000 * 4; ++i) {
            ++res;
        }
    }
    volatile uint64_t res1 = res; 
    assert(res > 100000);
    (void)res1;
}
BENCHMARK(singlethread_inc);

static void multithread_inc_atomic(benchmark::State &state) {
    static std::atomic<uint64_t> res{0};
    if (state.thread_index == 0) {
        res = 0;
    }
    for (auto _: state) {
        for (int i = 0; i < 1000000; ++i) {
            res.fetch_add(1);
        }
    }
    if (state.thread_index == 0) {
        assert(res > 100000);
    }
}
BENCHMARK(multithread_inc_atomic)->Threads(4);


BENCHMARK_MAIN();
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
