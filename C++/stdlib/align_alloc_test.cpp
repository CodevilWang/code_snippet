// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <stdlib.h>
void allign_alloc(int size, int cache_line_size) {
    void* base = malloc(size + cache_line_size);
    printf("%lld\n", (uintptr_t)base);
    printf("%lu\n", (uintptr_t)((unsigned char*)base + cache_line_size) & -cache_line_size);
    printf("%u\n", sizeof(uintptr_t));
    return ;
}
int main() {
    allign_alloc(10, 64);
    printf("%d\n", 56 & -64);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
