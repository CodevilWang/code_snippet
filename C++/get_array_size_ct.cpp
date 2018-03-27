// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
// get array size during compile time
#include <stdio.h>
template<typename T, size_t N>
char(&ArraySizeHelper(T(&data)[N]))[N];
#define get_array_size(one_array) (sizeof(ArraySizeHelper(one_array)))
int main() {
    char a[10];
    printf("%zu\n", get_array_size(a));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
