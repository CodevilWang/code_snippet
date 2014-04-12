/***************************************************************************
 * 
 * Copyright (c) 2014 Codevil, personal. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file print.h
 * @author codevil(codevil.w.m@gmail.com)
 * @date 2014/04/12 22:10:09
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef CODE_SNIPPET_CPLUS_PRINT_H 
#define CODE_SNIPPET_CPLUS_PRINT_H
#include <iostream>

template<class cls1>
void print(const cls1& first)
{
    std::cout << first << std::endl;
}

template<class cls1, class... cls>
void print(const cls1& first, const cls&... args)
{
    std::cout << first << std::endl;
    print(args...);
}


#endif  // CODE_SNIPPET_C++_PRINT_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
