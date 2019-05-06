// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <iostream>
#include <Eigen/Dense>
using Eigen::MatrixXd;
using Eigen::Matrix3d;
using Eigen::VectorXd;
static const uint32_t row_col = 100;
static const uint32_t total_num = 10000;
typedef Eigen::Matrix<double, row_col, row_col, Eigen::ColMajor> MatrixXColM; 
typedef Eigen::Matrix<double, row_col, row_col, Eigen::RowMajor> MatrixXRowM; 
static void bench_matrix_product() {
    // MatrixXd mata = Eigen::Matrix<double, row_col, row_col, Eigen::ColMajor>::Random();
    // MatrixXd matb = Eigen::Matrix<double, row_col, row_col, Eigen::ColMajor>::Random();
    MatrixXColM mata = MatrixXColM::Random();
    // MatrixXRowM matb = MatrixXRowM::Random();
    MatrixXRowM matb = MatrixXRowM::Random();
    for (int i = 0; i < total_num; ++i) {
         MatrixXColM ret = mata * matb;
    }
}

static void bench_matrix_product_rowmajor() {
    MatrixXRowM mata = MatrixXRowM::Random();
    // MatrixXRowM matb = MatrixXRowM::Random();
    MatrixXColM matb = MatrixXColM::Random();
    for (int i = 0; i < total_num; ++i) {
         MatrixXRowM ret = mata * matb;
    }
}
int main(int argc, char** argv) {
    // bench_matrix_product_rowmajor();
    bench_matrix_product();
    // if (argc > 1) {
    //     printf("bench_matrix_product\n");
    //     bench_matrix_product();
    // } else {
    //     printf("bench_matrix_product_rowmajor\n");
    //     bench_matrix_product_rowmajor();
    // }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
