// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <thread>
#include <chrono>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/Function.h>
void work() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    printf("after sleep 10000 ms\n");
}
int main() {
    // work(10);
    printf("heer\n");
    // work(1000);
    printf("heer\n");
#ifdef THREADED_EX
    folly::ThreadedExecutor th_ex;
#elif defined THREAD_POOL_EX
    folly::CPUThreadPoolExecutor th_ex{4};
#endif
    th_ex.add(folly::Function<void()>(work));
    th_ex.add(folly::Function<void()>(work));
    th_ex.add(folly::Function<void()>(work));
    th_ex.add(folly::Function<void()>(work));
    // th_ex.add(work(3000));
    // th_ex.add(work(2000));
    // th_ex.add(work(5000));
    // th_ex.add(work(4000));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
