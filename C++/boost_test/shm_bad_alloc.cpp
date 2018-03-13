// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)

#include <boost/interprocess/managed_shared_memory.hpp> 
#include <iostream> 

int main() 
{ 
  	try 
  	{ 
  	  boost::interprocess::shared_memory_object::remove("Highscore"); 
  	  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
  	  int *i = managed_shm.construct<int>("Integer")[4096](99); 
  	} 
  	catch (boost::interprocess::bad_alloc &ex) 
  	{ 
  	  std::cerr << ex.what() << std::endl; 
  	} 
	return 0;
} 

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
