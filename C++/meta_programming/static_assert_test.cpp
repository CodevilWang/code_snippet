// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <stdint.h>
#include <type_traits>
int main () {
    int v = 10;
    static_assert(sizeof(v) == 4, "wrong size for int.");
    using my_int = int;
    static_assert(std::is_same<my_int, int32_t>::value, "wrong size for int.");
    static_assert(std::is_same<my_int, decltype(v)>::value, "wrong size for int.");
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
