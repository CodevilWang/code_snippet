/***************************************************************************
 * 
 * Copyright (c) 2019 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file false_share_perf.cpp
 * @author work(com@baidu.com)
 * @date 2019/07/07 22:29:51
 * @brief 
 *  
 **/


//./perf stat -B -e
//cache-references,cache-misses,cycles,instructions,branches,faults,migrations,context-switches
//false_share_perf 1  
#include <stdio.h>
#include <thread>
int32_t data[2];
#define MAX_NUM 10000000

void work(int idx) {
    for (int i = 0; i < MAX_NUM; ++i) {
        data[idx] += 1;
    }
}

using aligned_type = typename std::aligned_storage<sizeof(uint32_t), 64>::type;
aligned_type data_aligned[2];

void work_aligned(int idx) {
    uint32_t* value = (uint32_t*)(data_aligned + idx);
    for (int i = 0; i < MAX_NUM; ++i) {
        (*value) += 1;
    }
}

int main(int argc, char** argv) {

    if (argc >= 2) {
        std::thread t1(work_aligned, 0);
        std::thread t2(work_aligned, 1);
        t1.join();
        t2.join();
        printf("first %u\t%u\n", *(uint32_t*)(data_aligned + 0), *(uint32_t*)(data_aligned + 1));
    
    } else {
        std::thread t1(work, 0);
        std::thread t2(work, 1);
        t1.join();
        t2.join();
        printf("second %d\t%d\n", data[0], data[1]);
    }
    
    return 0;
}




















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
