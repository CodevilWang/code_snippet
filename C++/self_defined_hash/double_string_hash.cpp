// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <stdio.h>
#include <set>
#include <unordered_set>
#include <string>
struct DoubleString {
    std::string first;
    std::string second;
    bool operator==(const DoubleString& oth) const {
        return first == oth.first && second == oth.second;
    }
};
template<>
struct std::hash<DoubleString> {
    typedef std::size_t result_type;
    typedef DoubleString argument_type;
    result_type operator() (argument_type const & ds) const {
        return 1;
    }
};
int main() {
    DoubleString s1 = {"abc", "def"};
    DoubleString s2 = {"def", "hij"};
    printf("%d\n", s1 == s2);
    std::unordered_set<DoubleString> dss;
    // std::set<DoubleString> dss;
    dss.insert(s1);
    dss.insert(s2);
    printf("%lu\n", dss.size());
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
