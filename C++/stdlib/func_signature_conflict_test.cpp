// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
// first translation unit
#include <stdio.h>
#include <type_traits>
 
struct X {
    enum { value1 = true, value2 = true };
};
 
template<class T, std::enable_if_t<T::value1, int> = 0>
void func() {} // #1
 
template void func<X>();
 
// second translation unit
template<class T, std::enable_if_t<T::value2, int> = 0>
void func() {} // #3
 
// template void func<X>(); //#4
int main() {
    printf("hello world\n");
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
