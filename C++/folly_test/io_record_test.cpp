// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include "folly/io/RecordIO.h" 
int main() {
    folly::File f("test_data", O_WRONLY | O_CREAT);
    folly::RecordIOWriter writer(std::move(f));
    const char* data = "hello record io.";
    size_t data_len = strlen(data);
    writer.write(folly::IOBuf::wrapBuffer(data, data_len));
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
