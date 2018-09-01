// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <vector>
double d_add (double a, double b) {
    return a + b;
}
template<typename f>
struct make_tuple_of_params;

template<typename Ret, typename... Args>
struct make_tuple_of_params<Ret(Args...)> {
    using type = std::tuple<Args...>;
};

template<typename F>
using make_type_of_params_t = typename make_tuple_of_params<F>::type;

int main() {
    // make_type_of_params_t<decltype(d_add)> v; 
    static_assert(std::is_same<make_type_of_params_t<decltype(d_add)>, std::tuple<double, double>>::value, "wrong params type");
    make_type_of_params_t<decltype(d_add)> v = {1.0, 2.0};
    // std::tuple<double, double> v{1.0, 2.0};
    printf("%f\n", std::get<0>(v));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
