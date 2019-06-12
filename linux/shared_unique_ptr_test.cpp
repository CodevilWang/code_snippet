// Copyright 2019 All Rights Reserved.
// Author: taoran07@baidu.com 
#include <stdio.h>
#include <memory>
int main() {
    std::unique_ptr<int[]> u_int_array(new int[10]);
    std::shared_ptr<int> s_int_array(new int[10], [](int* p) {
            delete[] p;
          });
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
