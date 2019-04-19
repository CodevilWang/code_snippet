// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <boost/context/all.hpp>
#include <stdio.h>

namespace ctx = boost::context;
ctx::detail::fcontext_t fc_avg, fc_input, fc_main;
bool b_quit = false;

struct average_args
{
    int * source;
    int sum;
    int count;
    int average;
    int task_;
};

void average_task(ctx::detail::transfer_t t)
{
    average_args* args = (average_args*)t.data;
    args->sum = 0;
    args->count = 0;
    args->average = 0;
    while (true)
    {
        args->sum += *args->source;
        ++args->count;
        args->average = args->sum / args->count;
        ctx::detail::jump_fcontext(t.fctx, 0);
    }

    printf("ERROR: should not reach the end of average function\n");
}

struct input_args
{
    average_args* aa;
    int * target;
    int task_;
};

void input_task(ctx::detail::transfer_t t)
{
    input_args* pia = (input_args*)t.data;
    // ctx::detail::transfer_t _t;
    // bool first = true;

    while (true)
    {
        printf("number: ");
        int ret = scanf("%d", pia->target);
        if (ret != 1)
        {
            b_quit = true;
            return;
        }
        ctx::detail::jump_fcontext(t.fctx, 0);
        // if (first) {
        //     _t = ctx::detail::jump_fcontext(t.fctx, 0);
        //     first = false;
        // } else {
        //     ctx::detail::jump_fcontext(_t.fctx, 0);
        // }
    }
    printf("ERROR: should not reach the end of input function\n");
}

int main()
{
    int share = -1;
    average_args aa = {&share};
    input_args ia = {&aa, &share};

    size_t size(102400);
    void* stack_buffer = std::malloc(size);
    fc_input = ctx::detail::make_fcontext(stack_buffer, size, input_task);

    // construct the average task
    void* stack_buffer_avg = std::malloc(size);
    fc_avg = ctx::detail::make_fcontext(stack_buffer_avg, size, average_task);
    
    ctx::detail::transfer_t t_input = {fc_input, 0};
    ctx::detail::transfer_t t_avg = {fc_avg, 0};

    while (!b_quit)
    {
        t_input = ctx::detail::jump_fcontext(t_input.fctx, &ia);
        t_avg = ctx::detail::jump_fcontext(t_avg.fctx, &aa);
        // printf("hello\n");
        printf("sum=%d count=%d average=%d b_quit=%d\n", aa.sum, aa.count, aa.average, b_quit);
    }
    printf("main: done\n");
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */

