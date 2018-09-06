// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <atomic>
struct Xs {
    long x;
};
struct Ys {
    long x;
    long y;
};
struct Zs {
    long x;
    long y;
    long z;
};
struct As {
    int x;
    int y;
    int z;
};
struct Bs {
    long x;
    int y;
};
int main() {
    long x;
    std::atomic<long> a(0);
    std::atomic<Ys> b({0, 0});
    std::atomic<Zs> c({0, 0, 0});
    // printf("%d\t%d\t%d\n", std::atomic<long>::is_lock_free(), b.is_lock_free(), c.is_lock_free());
    printf("%d\n", std::atomic<long>::is_lock_free());
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
