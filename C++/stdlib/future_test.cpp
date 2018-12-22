// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <future>
#include <iostream>
#include <chrono>

bool is_prime(int64_t x) {
    for (int64_t i = 2; i < x; ++i) {
        if (x % i == 0) {
            std::cout << " not prime by " << i << std::endl;
            return false;
        }
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    int64_t value = 444444443;
    std::future<bool> f = std::async(is_prime, value); 
    std::cout << "start computing" << std::endl;
    std::chrono::milliseconds span(100);
    while (f.wait_for(span) == std::future_status::timeout) {
        std::cout << ".";
        // std::cout.flush();
    }
    bool x = f.get();
    std::cout << value << (x ? " is" : " is not") << " prime" << std::endl;
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
