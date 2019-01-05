// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
//
#include <iostream>
class T1 {
public:
    using abctype = int;
    static void func() {
        std::cout << "T1 func" << std::endl;
    }
};

class T2 {
public:
    static void func() {
        std::cout << "T2 func" << std::endl;
    }
};

template<typename T, typename U>
void func() {
    T::func();
    U::func();
}

template<typename T, typename = typename T::abctype>
void func2() {
    T::func();
}

int main() {
    func<T1, T2>();
    func2<T1>();
    func2<T2>();
    return 0;
}
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
