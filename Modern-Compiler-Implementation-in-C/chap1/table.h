// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
typedef struct table* Table_;
struct table {
    string id;
    int value;
    Table_ tail;
};

struct IntAndTable {
    int i;
    Table_ t;
};

Table_ Table(string id, int value, struct table* tail);
struct IntAndTable int_and_table(int i, Table_ t);
Table_ interpExplist(A_expList exp_list, Table_ t);
Table_ interpStm(A_stm s, Table_ t);
struct IntAndTable interpExp(A_exp e, Table_ t);

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
