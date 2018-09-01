// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <stdlib.h>
#include <queue>
class Queue : public std::priority_queue<int, std::vector<int>> {
    public:
        std::vector<int>& get_container() {
            return this->c;
        }
};
int main() {
    Queue q;
    q.push(10);
    q.push(7);
    q.push(6);
    q.push(129);

    for (auto& i : q.get_container()) {
        printf("%d\n", i);
    }
    printf("=======\n");
    while (!q.empty()) {
        printf("%d\n", q.top());
        q.pop();
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
