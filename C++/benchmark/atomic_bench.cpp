#include <atomic>
#include <mutex>
#include "benchmark/benchmark.h"
// from https://sdjournal.org/understanding-c-atomic-operations/

volatile unsigned long x0(0);

void BM_nonatomic(benchmark::State& state) {
  if (state.thread_index == 0) x0 = 0;
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(x0=42);
  }
}

std::mutex M;

void BM_lock(benchmark::State& state) {
  if (state.thread_index == 0) x0 = 0;
  while (state.KeepRunning()) {
    M.lock();
    benchmark::DoNotOptimize(x0=42);
    M.unlock();
  }
}

volatile std::atomic<int> x(0);
void BM_atomic(benchmark::State& state) {
  if (state.thread_index == 0) x = 0;
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(x=42);
  }
}
void BM_atomic_relaxed(benchmark::State& state) {
  if (state.thread_index == 0) x = 0;
  while (state.KeepRunning()) {
    x.store(42, std::memory_order_relaxed);
  }
}

#define ARGS(N) \
  ->Threads(N) \
  ->UseRealTime()
#define BENCHMARKS(BM) \
BENCHMARK(BM) ARGS(1); \
BENCHMARK(BM) ARGS(2); \
BENCHMARK(BM) ARGS(4); \
BENCHMARK(BM) ARGS(8); \
BENCHMARK(BM) ARGS(16); \
BENCHMARK(BM) ARGS(32); \
BENCHMARK(BM) ARGS(64); \
BENCHMARK(BM) ARGS(128)
BENCHMARKS(BM_nonatomic);
BENCHMARKS(BM_atomic);
BENCHMARKS(BM_atomic_relaxed);
BENCHMARKS(BM_lock);
BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
