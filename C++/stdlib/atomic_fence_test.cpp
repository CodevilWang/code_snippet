// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <atomic>
#include <vector>
#include <thread>

void main_work(std::atomic<uint64_t>* inc, uint64_t& check) {
    while (check < std::numeric_limits<uint64_t>::max()) {
        uint64_t value = check;
        check += 1;
        (*inc).store(value, std::memory_order_release);
    }
    printf("end main %llu\n", check);
}
void check_work(std::atomic<uint64_t>* inc, uint64_t& check) {
    while (true) {
        uint64_t value = (*inc).load(std::memory_order_acquire);
        if (value > check) {
            printf("break inc [%llu] check [%llu]\n", value, check);
            return;
        }
    }
}
int main() {
    std::atomic<uint64_t> inc_value;
    inc_value.store(0);
    uint64_t check_value = 0;
    printf("%llu\n", std::numeric_limits<uint64_t>::max());

    std::thread mt(main_work, &inc_value, std::ref(check_value));
    static const int THREAD_NUM = 10;
    std::vector<std::thread> tv;
    for (int i = 0; i < THREAD_NUM; ++i) {
        // tv.push_back(std::thread(check_work, &inc_value, std::ref(check_value)));
        std::thread p(check_work, &inc_value, std::ref(check_value));
        tv.push_back(std::move(p));
    }
    mt.join();
    for (int i = 0; i < THREAD_NUM; ++i) {
        tv[i].join();
    }

    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
