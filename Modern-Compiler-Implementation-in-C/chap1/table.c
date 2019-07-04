// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include "util.h"
#include "slp.h"
#include "table.h"

Table_ Table(string id, int value, struct table* tail) {
    Table_ t = malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;
    return t;
}

struct IntAndTable int_and_table(int i, Table_ t) {
    struct IntAndTable ret = {
        .i = i,
        .t = t
    };
    return ret;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
