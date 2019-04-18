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
void average_yield() { ctx::detail::jump_fcontext(&fc_main, 0); }

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
        average_yield();
    }

    printf("ERROR: should not reach the end of average function\n");
}

struct input_args
{
    average_args* aa;
    int * target;
    int task_;
};
void input_yield() { ctx::detail::jump_fcontext(&fc_main, 0); }

void input_task(ctx::detail::transfer_t t)
{
    input_args* pia = (input_args*)t.data;

    while (true)
    {
        printf("number: ");
        if (!scanf("%d", pia->target))
        {
            b_quit = true;
            return;
        }

        input_yield();
    }
    printf("ERROR: should not reach the end of input function\n");
}

int main()
{
    int share = -1;
    average_args aa = {&share};
    input_args ia = {&aa, &share};

    void* stack_buffer = std::malloc(8192);
    fc_input = ctx::detail::make_fcontext(stack_buffer, 8192, input_task);
    ctx::detail::transfer_t t_input({fc_input, &ia});

    // construct the average task
    void* stack_buffer_avg = std::malloc(8192);
    fc_avg = ctx::detail::make_fcontext(stack_buffer_avg, 8192, average_task);
    ctx::detail::transfer_t t_avg({fc_avg, &aa});

    while (!b_quit)
    {
        ctx::detail::jump_fcontext(&fc_input, t_input.data);
        ctx::detail::jump_fcontext(&fc_avg, t_avg.data);
        printf("sum=%d count=%d average=%d\n", aa.sum, aa.count, aa.average);
    }
    printf("main: done\n");
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
