// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <glog/logging.h>
#include <gflags/gflags.h>
int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    int a = 10;
    LOG(INFO) << "Found " << a << " apples";
    LOG(WARNING) << "Found " << a << " apples";
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
