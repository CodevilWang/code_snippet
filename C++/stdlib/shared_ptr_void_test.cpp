// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <memory>
std::shared_ptr<void> work(int value) {
    if (value == 0) {
        return std::make_shared<int>(10);
    }
    return nullptr;
}
int main() {
    std::shared_ptr<void> ret1 = work(11);
    if (ret1 == nullptr) {
        return 0;
    } else {
        std::shared_ptr<int> ret = std::static_pointer_cast<int>(ret1);
        printf("%d\n", *ret);
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
