// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <boost/interprocess/shared_memory_object.hpp> 
#include <iostream> 

int main() 
{ 
  boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write); 
  shdmem.truncate(1024); 
  std::cout << shdmem.get_name() << std::endl; 
  boost::interprocess::offset_t size; 
  if (shdmem.get_size(size)) 
    std::cout << size << std::endl; 
} 

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
