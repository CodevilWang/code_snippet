// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <cstddef>
#define lengthof(x) (sizeof(x) / sizeof(x[0]))

template<typename T, std::size_t N>
constexpr std::size_t lengthof2(T(&)[N]) {
    return N;
}

int main () {
    int a[10] = {1};
    printf("%d\t%zu\t%zu\n", a[7], lengthof(a), lengthof2(a));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
