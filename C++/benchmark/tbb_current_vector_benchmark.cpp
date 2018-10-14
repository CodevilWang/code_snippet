#include <atomic>
#include <mutex>
#include "benchmark/benchmark.h"
#include "tbb/concurrent_vector.h"

static std::vector<int> values;
static std::mutex M;
void BM_mutex_vector(benchmark::State& state) {
  if (state.thread_index == 0) values.clear(); 
  while (state.KeepRunning()) {
    for (int i = 0; i < 1000000; ++i) {
        M.lock();
        values.push_back(i);
        M.unlock();
    }
  }
}

static tbb::concurrent_vector<int> v;
void BM_current_vector(benchmark::State& state) {
  if (state.thread_index == 0) v.clear(); 
  while (state.KeepRunning()) {
    for (int i = 0; i < 1000000; ++i) {
        v.push_back(i);
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
BENCHMARKS(BM_mutex_vector);
BENCHMARKS(BM_current_vector);
BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
