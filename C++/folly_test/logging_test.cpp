// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)

#include <stdio.h>
#include <folly/init/Init.h> 
#include <folly/logging/Init.h> 
#include <folly/logging/xlog.h> 
FOLLY_INIT_LOGGING_CONFIG(
    ".=WARNING,folly=INFO; default:async=true,sync_level=WARNING");
int main(int argc, char** argv) {
    XLOG(INFO) << "Test XLOG INFO before folly init";
    XLOG(ERR) << "Test XLOG ERR before folly init";
    auto init = folly::Init(&argc, &argv);
    XLOG(INFO) << "Test XLOG INFO after folly init";
    XLOG(ERR) << "Test XLOG ERR after folly init";
    return 0;

}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
