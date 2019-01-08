// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <algorithm>
template<typename T>
void foo(T x) {
    puts(__PRETTY_FUNCTION__);
}

unsigned  f() {
    return 100u;
}


int main() {
    foo(4);
    foo(4.2);
    foo("Hello World.");
    printf("%u\n", std::max(f(), 42u));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
