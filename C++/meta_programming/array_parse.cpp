// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <vector>
#include <boost/lexical_cast.hpp>

template<typename T>
bool get_array(const std::vector<std::string>& data, std::vector<T>* res) {
    if (!res) {
        fprintf(stderr, "input fail.");
        return false;
    }
    
    res->clear();
    res->reserve(data.size());
    for (int i = 0; i < data.size(); ++i) {
        try {
            res->push_back(boost::lexical_cast<T>(data[i]));
        } catch (boost::bad_lexical_cast &) {
            fprintf(stderr, "bad cast %s", data[i].c_str());
            continue;
        }
    }
    return true;
}
int main() {
    std::vector<std::string> data = {"1", "2", "3"};
    std::vector<int> res;
    assert(get_array(data, &res));
    for (auto& v : res) {
        printf("%d\t", v);
    }
    printf("\n");

    std::vector<std::string> data1 = {"1", "2", "3"};
    std::vector<float> res1;
    assert(get_array(data1, &res1));
    for (auto& v : res1) {
        printf("%f\t", v);
    }
    printf("\n");
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
