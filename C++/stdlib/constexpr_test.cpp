// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <stdlib.h>
#include <array>
constexpr int pow(int base, int num) {
#ifdef C_14
    if (num == 0) {
        return 1;
    } else {
        return base * pow(base, num - 1);
    }
#elif defined C_!!
    return num == 0 ? 1 : base * pow(base, num - 1);
#endif
}
int main() {
    using container_type = std::array<int, pow(3, 1)>;
    container_type data;
    container_type::iterator it = data.begin();
    for (; it != data.end(); ++it) {
        *it = rand();
        printf("%d\n", *it);
    }
    return 0;
}





















/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
