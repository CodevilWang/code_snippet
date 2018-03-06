// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
// use -D_GLIBCXX_DEBUG will abort during runtime
#include <stdio.h>
#include <list>
int main() {
    std::list<int> l1 {1, 2, 3, 4 ,5};
    std::list<int> l2 {5, 4, 3, 2, 1};
    l1.merge(l2);
    std::list<int>::iterator it = l1.begin();
    while(it != l1.end()) {
        printf("%d\n", *it);
        ++it;
    }
    return 0;
}


/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
