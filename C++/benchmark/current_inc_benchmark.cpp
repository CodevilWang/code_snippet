#include <atomic>
#include <mutex>
#include <pthread.h>
#include "benchmark/benchmark.h"
#include "folly/synchronization/MicroSpinLock.h"

static uint64_t value;
static std::mutex M;
void BM_mutex_inc(benchmark::State& state) {
  if (state.thread_index == 0) value = 0;
  while (state.KeepRunning()) {
    for (int i = 0; i < 1000000; ++i) {
        M.lock();
        ++value;
        M.unlock();
    }
  }
}

static std::atomic<uint64_t> v;
void BM_atomic_inc(benchmark::State& state) {
  if (state.thread_index == 0) v = 0; 
  while (state.KeepRunning()) {
    for (int i = 0; i < 1000000; ++i) {
        ++v;
    }
  }
}

// static uint64_t v0; 
// static pthread_spinlock_t p_spin_l;
// void BM_pthread_spin_inc(benchmark::State& state) {
//   if (state.thread_index == 0) v0 = 0; 
//   while (state.KeepRunning()) {
//     for (int i = 0; i < 1000000; ++i) {
//         pthread_spin_lock(&p_spin_l);
//         ++v0;
//         pthread_spin_unlock(&p_spin_l);
//     }
//   }
// }
//
static uint64_t v0; 
static folly::MicroSpinLock p_spin_l;
void BM_microspin_inc(benchmark::State& state) {
  if (state.thread_index == 0) {
      v0 = 0; 
      p_spin_l.init();
  }
  while (state.KeepRunning()) {
    for (int i = 0; i < 1000000; ++i) {
        p_spin_l.lock();
        ++v0;
        p_spin_l.unlock();
    }
  }
}


#define ARGS(N) \
  ->Threads(N) \
  ->UseRealTime()
#define BENCHMARKS(BM) \
BENCHMARK(BM) ARGS(1); \
BENCHMARK(BM) ARGS(2); \
BENCHMARK(BM) ARGS(4); \
BENCHMARK(BM) ARGS(8);
BENCHMARKS(BM_mutex_inc);
BENCHMARKS(BM_atomic_inc);
BENCHMARKS(BM_microspin_inc);
// BENCHMARKS(BM_pthread_spin_inc);
BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
