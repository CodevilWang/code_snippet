// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <vector>
#include "pthread.h" 
#include "tbb/concurrent_vector.h"
#include "folly/FBVector.h"
// std::vector && folly::fbvector will crash for memory issures
static const int VSIZE = 10000000;
static const int thread_num = 10;
void* work(void* args) {
#ifdef USE_TBB
    using vtypes = tbb::concurrent_vector<int>;
#elif defined(USE_FOLLY)
    using vtypes = folly::fbvector<int>; 
#else
    using vtypes = std::vector<int>; 
#endif
    vtypes* values = (vtypes*)args;
    for (int i = 0; i < 100000; ++i) {
        values->push_back(i);
    }
    return NULL;
}
int main() {
#ifdef USE_TBB
    tbb::concurrent_vector<int> values;
#elif defined(USE_FOLLY)
    folly::fbvector<int> values;
#else
    std::vector<int> values;
#endif
    pthread_t thread_pool[thread_num];
    for (int i = 0; i < thread_num; ++i) {
        pthread_create(&(thread_pool[i]), NULL, work, &values);
    }
    for (int i = 0; i < thread_num; ++i) {
        pthread_join(thread_pool[i], NULL);
    }
    printf("%zu\n", values.size());
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
