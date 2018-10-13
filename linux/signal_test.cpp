// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <signal.h>
static uint64_t res = 0;
static void signal_handler(const int sig) {
    printf("catch signal[%d] [%llu]\n", sig, res);
    _exit(1);
}
int main() {
    signal(SIGTERM, signal_handler);
    printf("[%d] started.\n", getpid());
    for (uint64_t i = 0; i < INT_MAX; ++i) {
        ++res;
    }
    printf("res %llu\n", res);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
