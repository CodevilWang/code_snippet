// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <type_traits>
#include <atomic>
#include <iostream>
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_pod<std::atomic<int>>::value << "\n";
    std::cout << std::is_trivial<std::atomic<int>>::value << "\n";
    return 0;
}
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
