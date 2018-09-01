// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <tuple>
#include <utility>

template<typename F, typename params, typename... others>
size_t count_num() {
    return sizeof...(others);
}

template<std::size_t... I, typename params>
int show_value(params p) {
    printf("%d\t%d\t%d\n", std::get<I>(p)...);
    return 0;
}
int main() {
    printf("%zu\n", count_num<int, int, int, int>());
    show_value<1, 2, 3>(std::make_tuple(1, 2, 3, 4, 5));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
