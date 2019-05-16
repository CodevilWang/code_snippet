// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <string>
#include <sstream>
#define TCON(a, b) a##b
template <typename T, T default_value = T{}>
class TestC {
public:
    void work() {
        std::ostringstream oss;
        oss << default_value;
        printf("%s\n", oss.str().c_str());
    }
};
int main() {
    TestC<int, 10> tc;
    tc.work();
    const char* tc10 = "def";
    printf("%s\n", TCON(tc, 10));
    using TestD = TestC<int, 10>;
    const char* TestD10 = "abc";
    printf("%s\n", TCON(TestD, 10));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
