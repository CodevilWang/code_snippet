// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <cxxabi.h>
#include <string>
int main() {
    std::string str = {"abcdef"};
    int status;
    printf("%s\n", typeid(str).name());
    printf("%s\n", abi::__cxa_demangle(typeid(str).name(), 0, 0, &status));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
