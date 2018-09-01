// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <vector>
#include <numeric>
int main() {
    std::vector<int> vs;
    vs.resize(5);
    std::iota(vs.begin(), vs.end(), 0);
    for (auto& i : vs) {
        printf("%d\n", i);
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
