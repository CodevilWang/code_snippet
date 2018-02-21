// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
//
// signal interrupt only one thread 
// kill -USR1 thread num
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <iostream>
#include <thread>
#include <chrono>

#ifdef LINUX
pid_t gettid() {
    return static_cast<pid_t>(::syscall(SYS_gettid));
}
#endif
#ifdef MACOS 
#include <pthread.h>
pid_t gettid() {
    return static_cast<pid_t>(pthread_mach_thread_np(pthread_self())); 
}
#endif


void do_something() {
    printf("this thread is [%llu] starting\n", gettid()); 
    std::cout << "this thread is " << gettid() << "startting" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(30000));
    printf("this thread is [%llu] end\n", gettid()); 
}
void usr1_sig_handle(int signum) {
    printf("this thread is [%llu] catch signal\n", gettid()); 
}
void do_something_signal() {
    signal(SIGUSR1, usr1_sig_handle);
    printf("this thread is [%llu] starting\n", gettid()); 
    std::this_thread::sleep_for(std::chrono::milliseconds(30000));
    printf("this thread is [%llu] end\n", gettid()); 
}

int main() {
    printf("main thread [%llu]\n", gettid());
    signal(SIGUSR1, usr1_sig_handle);
    std::thread p1(do_something_signal);
    std::thread p2(do_something);
    std::thread p3(do_something);
    std::thread p4(do_something);
    std::thread p5(do_something);
    std::thread p6(do_something);
    p1.join();
    p2.join();
    p3.join();
    p4.join();
    p5.join();
    p6.join();
    return 0;
}





















/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
