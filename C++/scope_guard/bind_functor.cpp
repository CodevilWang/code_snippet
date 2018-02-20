// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)

#include <stdio.h>
#include <boost/bind.hpp>
class Test {
    public:
        int work0() {
            printf("int work0\n");
            return 0;
        }
        int work1(int val) {
            printf("int work1 %d\n", val); 
            return 0;
        }
};
int main() {
    Test t;
    auto work0_f = boost::bind<int>(&Test::work0, t);
    auto work1_f = boost::bind<int>(&Test::work1, t, _1);
    work0_f();
    work1_f(10);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
