// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include <thread>
// __thread int value = 10; 
thread_local int value = 10; 
int work() {
    int num = rand() % 10;
    std::this_thread::sleep_for(std::chrono::seconds(num));
    printf("start value %d num %d\n", value, num);
    printf("res %d\n", value + num);
    return 0;
}
int main() {
    std::vector<std::thread> tv;
    for (int i = 0; i < 10; ++i) {
        tv.push_back(std::thread(work));
    }
    for (int i = 0; i < 10; ++i) {
        tv[i].join(); 
    }
    printf("end\n");
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
