// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <iostream>
#include <string>
#include <boost/scoped_ptr.hpp> 
#include <boost/shared_ptr.hpp> 
#include <vector> 

template <typename T> 
T *create() 
{ 
      return new T; 
} 

int main() 
{ 
    std::vector<boost::shared_ptr<int>> v; 
    v.push_back(boost::shared_ptr<int>(create<int>())); 
    return 0;
} 
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
