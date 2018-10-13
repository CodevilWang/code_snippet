// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
void signal_handler(const int sig) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("signal [%ld]\n", tv.tv_sec);
    _exit(1);
}
int main() {
    signal(SIGTERM, signal_handler);
    struct timeval tv0;
    gettimeofday(&tv0, NULL);
    printf("before sleep %ld [%d]\n", tv0.tv_sec, getpid());
    sleep(10);
    gettimeofday(&tv0, NULL);
    printf("after sleep %ld\n", tv0.tv_sec);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
