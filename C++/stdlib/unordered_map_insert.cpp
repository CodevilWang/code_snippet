// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <unordered_map>
#include <string>
#include <vector>
void work(const std::pair<std::string, uint32_t>& value) {
    printf("%s\t%d\n", value.first.c_str(), value.second);
}
int main () {
    std::vector<const std::string*> order;
    std::unordered_map<std::string, std::string> dat;
    auto ret = dat.insert({"abc", std::string("def")});
    if (ret.second) {
        printf("Success.\n");
    }
    // printf("%s\n", ret.first->first.c_str());
    order.push_back(&(ret.first->first));
    ret = dat.insert({"i", "defh"});
    order.push_back(&(ret.first->first));
    ret = dat.insert({"j", "defi"});
    order.push_back(&(ret.first->first));
    for (auto& value : order) {
        printf("data %s\n", dat[*value].c_str());
    } 
    work({"anbc", 11});
    return 0;
}




















/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
