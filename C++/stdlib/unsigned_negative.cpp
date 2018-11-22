// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <limits>
#include <atomic>
#include <stdlib.h>
int main() {
    uint32_t a = -1;
    printf("%u\n", std::numeric_limits<uint32_t>::max() / 2);
    printf("%u\n", a);
    printf("%d\n", a == std::numeric_limits<uint32_t>::max() / 2);
    alignas(128) std::atomic<int> b;
    printf("%lu\n", (uintptr_t)(&b));
    alignas(64) std::atomic<int> c;
    printf("%lu\n", (uintptr_t)(&c));
    alignas(16) std::atomic<int> d;
    printf("%lu\n", (uintptr_t)(&d));
    b.store(0, std::memory_order_relaxed);
    ++b;
    printf("%d\n", b.load(std::memory_order_relaxed));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
