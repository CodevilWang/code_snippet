// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>
int main() {
    Eigen::Tensor<float, 1> t(10);
    t(0) = 1.0f;
    t(1) = 2.0f;
    t(2) = 3.0f;
    t(3) = 4.0f;
    printf("%f\t%f\t%f\n", t(0), t(1), t(2));
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    Eigen::TensorMap<Eigen::Tensor<float, 2>> a(data, 3, 4);
    printf("%f\t%f\t%f\n", a(0, 1), a(1, 1), a(2, 2));
    a(0, 0) = 10;
    printf("%f\t%f\n", a(0, 0), data[0]);
    Eigen::TensorMap<Eigen::Tensor<float, 2>> b(data, 1, 12);
    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 12; ++j) {
            printf("%f\t", b(i, j));
        }
    }
    printf("\n");
    return 0;
}




















/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
