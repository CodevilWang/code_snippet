/***************************************************************************
 * 
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 /**
 * @file cal_sum_template.h
 * @author cdwm(cdwm@baidu.com)
 * @date 2017/08/29 17:11:06
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef CODE_SNIPPET_CAL_SUM_TEMPLATE_H
#define CODE_SNIPPET_CAL_SUM_TEMPLATE_H

template <int N>
int sum() {
    return N + sum<N - 1>();
}
template<>
int sum<1>() {
    return 1;
}

#endif  // CODE_SNIPPET_CAL_SUM_TEMPLATE_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
