// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
class TestA {
public:
    virtual ~TestA() {}
    int a;
    int b;
};
class TestB {
    public:
        int c;
        int d;
};
class TestC : public TestA {
    public:
        virtual ~TestC() {}
};
int main() {
    TestC* ta = new TestC();
    TestC* tb = new TestC();
    TestC* tc = dynamic_cast<TestC*>(ta);
    if (tc == nullptr) {
        printf("tc null\n");
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
