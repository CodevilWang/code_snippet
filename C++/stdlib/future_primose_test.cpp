// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <sys/time.h>
#include <future>
#include <chrono>
#include <iostream>
#include <thread>

static const int64_t MAX_VALUE = 44443;
void cal_max_prime(std::promise<int64_t>&& p) {
    int64_t max_prime = 2;
    for (int64_t i = 2; i <= MAX_VALUE; ++i) {
        bool is_prime = true;
        for (int j = 2; j < i; ++j) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            max_prime = i;
        } 
    }
    p.set_value(max_prime);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("cal_max_prime end %ld\n", tv.tv_sec); 
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    gettimeofday(&tv, NULL);
    printf("thread sleep end %ld\n", tv.tv_sec); 
}
int main() {
    std::promise<int64_t> p;
    std::future<int64_t> f = p.get_future();
    std::thread t(cal_max_prime, std::move(p));
    std::chrono::milliseconds span(100);
    std::cout << "cal ";
    std::flush(std::cout);
    while (f.wait_for(span) == std::future_status::timeout) {
        std::cout << ".";
        std::flush(std::cout);
    }
    std::cout << std::endl; 
    std::flush(std::cout);
    int64_t fv = f.get();
    std::cout << "res value " << fv << std::endl; 
    t.join();
    return 0;
}


/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
