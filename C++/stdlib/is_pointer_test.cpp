// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <stdint.h>
#include <type_traits>
template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B,T>::type;
// template <class T, class = std::enable_if_t<std::is_pointer<T>::value>>
template <class T, class = enable_if_t<std::is_pointer<T>::value>>
using owner = T;
template<typename T>
struct Test {
    T a;
    void show() {
        printf("%d\n", a);
    }
};
template<>
struct Test<uint32_t> {
    void show() {
        printf("second show \n");
    }
};
int main() {
    printf("%d\n", std::is_pointer<int*>::value);
    owner<int*> a = new int(109);
    // owner<int> b = 10;
    printf("%d\n", *a);
    // printf("%d\n", b);
    Test<int> ti;
    ti.a = 10;
    ti.show();
    Test<uint32_t> ti2;
    ti2.show();
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
