// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <folly/FBString.h>
int main() {
    folly::fbstring a = "abc";
    printf("%s\n", a.c_str());
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
