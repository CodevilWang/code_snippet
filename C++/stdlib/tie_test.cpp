// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <tuple>
std::tuple<int, int> func(int a, int b) {
    std::tuple<int, int> tuple_res = std::make_tuple(a + 1, b + 1);
    const auto& t_res = tuple_res;
    printf("%d\t%d\n", std::get<0>(tuple_res), std::get<1>(tuple_res));
    printf("%d\t%d\n", std::get<0>(t_res), std::get<1>(t_res));
    static_assert(std::is_same<decltype(t_res), const std::tuple<int, int>&>::value, "type check failed");
    return tuple_res;
}
int main() {
    int first_value = -1;
    int second_value = -1;
    std::tie(first_value, second_value) = func(1, 2);
    printf("%d\t%d\n", first_value, second_value);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
