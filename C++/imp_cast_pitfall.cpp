// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <vector>

template<typename T>
class Array {
public:
    Array(int size) {
        _data.reserve(size);
    }
    const T&operator[] (int index) {
        return _data[index];
    }
    friend bool operator==(const Array<T>& lhs, const Array<T>& rhs) {
        return true;
    }
private:
    std::vector<T> _data;
};
int main() {
    Array<int> arr1(10);
    Array<int> arr2(10);
    if (arr1 == arr2) {
        printf("bingo\n");
    }
    if (arr1 == arr2[10]) {
        printf("pitfall\n");
    }
    return 0;
}




















/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
