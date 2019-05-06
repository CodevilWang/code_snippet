// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <benchmark/benchmark.h>
#include <iostream>
#include <Eigen/Dense>
using Eigen::MatrixXd;
using Eigen::Matrix3d;
using Eigen::VectorXd;
static const uint32_t row_col = 100;
typedef Eigen::Matrix<double, row_col, row_col, Eigen::ColMajor> MatrixXColM; 
typedef Eigen::Matrix<double, row_col, row_col, Eigen::RowMajor> MatrixXRowM; 
static void bench_matrix_product(benchmark::State &state) {
    // MatrixXd mata = Eigen::Matrix<double, row_col, row_col, Eigen::ColMajor>::Random();
    // MatrixXd matb = Eigen::Matrix<double, row_col, row_col, Eigen::ColMajor>::Random();
    MatrixXColM mata = MatrixXColM::Random();
    MatrixXRowM matb = MatrixXRowM::Random();
    while (state.KeepRunning()) {
        MatrixXColM ret = mata * matb;
    }
}
BENCHMARK(bench_matrix_product);

static void bench_matrix_product_rowmajor(benchmark::State &state) {
    MatrixXRowM mata = MatrixXRowM::Random();
    // MatrixXRowM matb = MatrixXRowM::Random();
    MatrixXColM matb = MatrixXColM::Random();
    while (state.KeepRunning()) {
         MatrixXRowM ret = mata * matb;
    }
}
BENCHMARK(bench_matrix_product_rowmajor);

// static void bench_push_back_reserve(benchmark::State &state) {
//     while (state.KeepRunning()) {
//         std::vector<int> v;
//         v.reserve(1);
//         v.push_back(42);
//     }
// }
// BENCHMARK(bench_push_back_reserve);


BENCHMARK_MAIN();

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
