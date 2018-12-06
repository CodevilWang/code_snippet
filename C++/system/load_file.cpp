// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
int main() {
    std::string file_name{"/Users/bytedance/Downloads/EpicInstaller-7.4.0.dmg"};
    const boost::interprocess::mode_t mode = boost::interprocess::read_only;
    boost::interprocess::file_mapping fm(file_name.c_str(), mode);
    boost::interprocess::mapped_region region(fm, mode, 0, 0);
    const char* begin = static_cast<const char*>(region.get_address());
    return 0;
}


/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
