// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <sys/time.h>
#include <type_traits>
#include <vector>
#include <thread>
static const uint32_t MAX_NUM = 1 << 20;
static const uint32_t THRD_NUM = 4;
using aligned_type = typename std::aligned_storage<sizeof(uint32_t), 64>::type;
void work(uint32_t* data, int idx) {
    uint32_t* value = (uint32_t*)data + idx;
    printf("%d\t%p\n", idx, value);
    uint32_t cnt = 0;
    while (cnt < MAX_NUM) {
        (*value) += 1;
        ++cnt;
    }
}
void work_aligned(aligned_type* data, int idx) {
    uint32_t* value = (uint32_t*)(data + idx);
    printf("%d\t%p\n", idx, value);
    uint32_t cnt = 0;
    while (cnt < MAX_NUM) {
        (*value) += 1;
        ++cnt;
    }
}
int main() {
#ifdef __ALIGN__
    // typename std::aligned_storage<sizeof(uint32_t), 64>::type data[THRD_NUM];
    aligned_type data[THRD_NUM];
#else
    uint32_t data[THRD_NUM];
#endif
    memset(data, 0, sizeof(data));
    std::vector<std::thread> t_vec;
    timeval ts;
    timeval te;
    gettimeofday(&ts, NULL);
#ifdef __ALIGN__
    for (int i = 0; i < THRD_NUM; ++i) {
        t_vec.push_back(std::thread(work_aligned, data, i));
    }
#else
    for (int i = 0; i < THRD_NUM; ++i) {
        t_vec.push_back(std::thread(work, data, i));
    }
#endif
    for (int i = 0; i < THRD_NUM; ++i) {
        t_vec[i].join();
    }
    gettimeofday(&te, NULL);
    printf("used %ld seconds %ld useconds\n", te.tv_sec - ts.tv_sec, te.tv_usec - ts.tv_usec);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
