// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <chrono>
class high_resolution_timer {
public:
    high_resolution_timer(): start_time_(take_time_stamp()) {}
    void restart() {
        start_time_ = take_time_stamp();
    }
    double elapsed() const {
        return double(take_time_stamp() - start_time_) * 1e-9;
    }
    std::uint64_t elapsed_nanoseconds() const {
        return take_time_stamp() - start_time_;
    }
private:
    uint64_t take_time_stamp() const {
        return (uint64_t)(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }
    uint64_t start_time_;
};
int main() {
    high_resolution_timer timer;
    timer.restart();
    int ret = 0;
    for(int i = 0; i < 1000000; ++i) {
        ret += 1;
    }
    printf("%lf\t%d\n", timer.elapsed(), ret);
    return 0;
}
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
