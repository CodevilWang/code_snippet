// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <folly/io/async/TimeoutManager.h>
#include <folly/io/async/AsyncTimeout.h>
#include <folly/io/async/EventBase.h>
void event_base_looop(void* arg) {
    std::atomic_bool* af = (std::atomic_bool*)(arg);
    int cnt = 0;
    while (!*af) {
        printf("hello world %d\n", cnt);
        cnt += 1;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
int main() {
    std::atomic_bool flag{false};
    folly::EventBase tm;
    std::thread bg_th = std::thread{event_base_looop, &flag};
    auto observer = folly::AsyncTimeout::schedule(std::chrono::seconds(5), tm, [&]() noexcept {
        std::cout << "atm hello, world!" << std::endl;
        flag = true;
    });
    tm.loop();
    bg_th.join();
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
