// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <vector>
#include <memory>
int main() {
    std::vector<float> data;
    data.push_back(1.0);
    data.push_back(1.2);
    float* in_data = data.data();
    printf("%f\t%f\n", *in_data, *(in_data + 1));
    std::shared_ptr<std::vector<float>> vp = std::make_shared<std::vector<float>>();
    vp->push_back(1.10012);
    vp->push_back(1.30012);
    in_data = vp->data();
    printf("%f\t%f\n", *in_data, *(in_data + 1));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
