// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <chrono>
#include <thread>
#include <folly/futures/Future.h>
int main() {
    folly::Promise<int> p;
    folly::Future<int> f = p.getFuture();
    folly::Future<int> ff = std::move(f);
    std::move(ff).then([] {
        printf("in future callbacks.\n");
    });
    std::thread t([]() ->int {
        for (int i = 0; i < 10; ++i) {
            printf("cur %d\n", i);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        return 0;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    p.setValue(10);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    t.join();

    auto f1 = folly::makeFuture(1).then([]() {
                    return 10;
                }).then([](int v) {
                        printf("value is %d\n", v);
                });

    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
