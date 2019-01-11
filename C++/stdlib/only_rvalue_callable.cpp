// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <utility> 
class Test {
    public:
        void show()&& {
            printf("helloworld\n");
        }
        void show()& {
            printf("helloworld 2\n");
        } 
};
int main() {
    Test t;
    std::move(t).show();
    t.show();
    return 0;
}





















/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
