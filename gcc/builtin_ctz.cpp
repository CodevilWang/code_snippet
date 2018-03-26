// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <stdio.h>
#include <assert.h>
int main() {
    // 1100100
    int a = 100;
    int b = 99;
    int c = 0b111000;
    assert(__builtin_ctz(a) == 2);
    assert(__builtin_ffs(b) == 1);
    assert(__builtin_ffs(c) == 4);
    printf("%d\n", __builtin_clz(a));
    assert(__builtin_clz(c) == 26);
    printf("%d\n", __builtin_popcount(a));
    printf("%d\n", __builtin_parity(a));
    assert(__builtin_popcount(b) == 4);
    assert(__builtin_parity(c) == 1);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
