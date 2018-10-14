// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include "tbb/concurrent_vector.h"
#include "folly/FBVector.h"
#include <limits.h> 
#include <sys/time.h> 
#include <vector>
static const int V_SIZE = 10000000;
int main() {
#ifdef USE_TBB
    tbb::concurrent_vector<int> c_vec;
#elif defined(USE_FOLLY)
    folly::fbvector<int> c_vec;
#else
    std::vector<int> c_vec;
#endif
    // c_vec.reserve(V_SIZE);
    timeval t0;
    gettimeofday(&t0, NULL);
    for (int i = 0; i < V_SIZE; ++i) {
        c_vec.push_back(i);
    }
    timeval t1;
    gettimeofday(&t1, NULL);
    int64_t res = 0;
    for (int i = 0; i < V_SIZE; ++i) {
        res += c_vec[i];
        if (res > INT_MAX) {
            res = 0;
        }
    }
    timeval t2;
    gettimeofday(&t2, NULL);
    printf("res is [%lld]\n", res);
    printf("start time is [%ld-%d]\n", t0.tv_sec, t0.tv_usec);
    printf("first phrase time is [%ld-%d]\n", t1.tv_sec, t1.tv_usec);
    printf("second phrase time is [%ld-%d]\n", t2.tv_sec, t2.tv_usec);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
