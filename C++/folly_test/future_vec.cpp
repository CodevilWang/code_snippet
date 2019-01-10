// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <vector>
#include <thread>
#include <future>

void work(std::promise<int>&& p, int i) {
    p.set_value(10);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * i));
}

int main() {
    std::vector<std::promise<int>> pv;
    std::vector<std::future<int>> fv;
    std::vector<std::thread> tv;
    for (int i = 0; i < 10; ++i) {
        std::promise<int> p;
        fv.push_back(p.get_future());
        pv.push_back(std::move(p));
        tv.push_back(std::thread(work, std::move(pv[i]), i));
    }
    for (int i = 0; i < 10; ++i) {
        printf("%d\t%d\n", i, fv[i].get());
    }
    for (int i = 0; i < 10; ++i) {
        tv[i].join();
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
