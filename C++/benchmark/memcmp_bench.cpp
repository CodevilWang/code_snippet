#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nmmintrin.h>
#include <benchmark/benchmark.h>

static int sse42_memcmp(void* s1, void* s2, size_t n) {

    if (n == 0 || (s1 == s2)) {
        return 0;
    }
    __m128i* ptr1 = reinterpret_cast<__m128i*>(s1);
    __m128i* ptr2 = reinterpret_cast<__m128i*>(s2);
    const uint8_t mode =
        _SIDD_UBYTE_OPS |
        _SIDD_CMP_EQUAL_EACH |
        _SIDD_NEGATIVE_POLARITY |
        _SIDD_LEAST_SIGNIFICANT;

    for (/**/; n != 0; ptr1++, ptr2++) {
        const __m128i a = _mm_loadu_si128(ptr1);
        const __m128i b = _mm_loadu_si128(ptr2);
        if (_mm_cmpestrc(a, n, b, n, mode)) {
            const auto idx = _mm_cmpestri(a, n, b, n, mode);
            const uint8_t b1 = (reinterpret_cast<char*>(ptr1))[idx];
            const uint8_t b2 = (reinterpret_cast<char*>(ptr2))[idx];
            if (b1 < b2) {
                return -1;
            } else if (b1 > b2) {
                return +1;
            } else {
                return 0;
            }
        } 
        if (n > 16) {
            n -= 16;
        } else {
            n = 0;
        }
    }

    return 0;
}
static void bench_memcmp(benchmark::State &state) {
    char a_array[1024];
    char b_array[1024];
    memset(a_array, 0, 1024);
    memset(b_array, 0, 1024);
    a_array[1023] = 1;
    b_array[1003] = 1;
    while (state.KeepRunning()) {
        assert(-1 == memcmp(a_array, b_array, 1024));
    }
}
BENCHMARK(bench_memcmp);

static void bench_memcmp_sse42(benchmark::State &state) {
    char a_array[1024] __attribute__((aligned(64)));
    char b_array[1024] __attribute__((aligned(64)));
    memset(a_array, 0, 1024);
    memset(b_array, 0, 1024);
    a_array[1023] = 1;
    b_array[1003] = 1;
    while (state.KeepRunning()) {
        assert(-1 == sse42_memcmp(a_array, b_array, 1024));
    }
}
BENCHMARK(bench_memcmp_sse42);

BENCHMARK_MAIN();

