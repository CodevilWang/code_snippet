// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <typeinfo>
#include <string>
template<class T>
class AnotherTemplate {
    public:
        int work = 100;
};
template<class T, int T::*member>
class FirstTemplate {
public:
    void work() {
        T a;
        printf("hello world %d\n", (a.*member));
    }
};
int main() {
    FirstTemplate<AnotherTemplate<std::string>, &AnotherTemplate<std::string>::work> c;
    c.work();
    return 0;
}






















/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
