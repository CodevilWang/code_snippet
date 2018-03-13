// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <iostream>
#include <string>
#include <boost/scoped_ptr.hpp> 
#include <boost/shared_ptr.hpp> 
boost::shared_ptr<char> get(const char* s) {
    int size = std::strlen(s);
    boost::shared_ptr<char> text(new char[size + 1]);
    std::strncpy(text.get(), s, size + 1);
    return text;
}
void print(char* text) {
    std::cout << text << std::endl;
}
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << argv[0] << " <data>" << std::endl;
        return 1;
    }
    boost::shared_ptr<char> text(get(argv[1]));
    print(text.get());
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
