// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <folly/synchronization/Rcu.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <sstream>
static const size_t ELE_NUM = 10;
struct IntArray {
public:
    int data[ELE_NUM];
};
std::atomic<IntArray*> data{new IntArray()};
std::atomic<int> cursor{0};
void reader() {
    while (true) {
        folly::rcu_reader r;
        std::ostringstream oss;
        IntArray* cur_ptr = data.load();
        for (int i = 0; i < ELE_NUM; ++i) {
            oss << cur_ptr->data[i] << " ";
        }
        printf("%s\n", oss.str().c_str());
    }
}
void writer() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        IntArray* cur_ptr = data.load();
        IntArray* new_ptr = new IntArray();
        for (int i = 0; i < ELE_NUM; ++i) {
            new_ptr->data[i] = cursor.load(); 
        }
        cursor += 1;
        data.store(new_ptr);
        folly::rcu_retire(cur_ptr);
    }
}
int main() {
    IntArray* raw_ptr = data.load(std::memory_order_acquire);
    for (int i = 0; i < ELE_NUM; ++i) {
        raw_ptr->data[i] = cursor.load();
    }
    std::vector<std::thread> tv;
    tv.emplace_back(writer);
    for (int i = 0; i < 5; ++i) {
        tv.emplace_back(reader);
    }
    for (int i = 0; i < tv.size(); ++i) {
        tv[i].join();
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
