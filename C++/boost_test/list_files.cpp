// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <boost/filesystem/operations.hpp>
#include <iostream>
int main() {
    typedef boost::filesystem::directory_iterator bfdi;
    bfdi begin(".");
    bfdi end;
    for (bfdi iter = begin; iter != end; ++iter) {
        boost::filesystem::file_status fs = boost::filesystem::status(*iter);
        switch(fs.type()) {
            case boost::filesystem::regular_file:
                std::cout << "FILE\t";
                break;
            case boost::filesystem::directory_file:
                std::cout << "DIRECTORY\t";
                break;
            default:
                std::cout << "OTHERS\t";
                break;
        }
        if (fs.permissions() & boost::filesystem::owner_write) {
            std::cout << "W\t";
        } else {
            std::cout << "NW\t";
        }
        std::cout << *iter << std::endl;
    }
    return 0;
}








/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
