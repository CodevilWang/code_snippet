#include <stdio.h>
#include "util.h" 
#include "slp.h" 
#include "prog1.h" 
#include "table.h" 

// struct A_stm_ {enum {A_compoundStm, A_assignStm, A_printStm} kind;
//              union {struct {A_stm stm1, stm2;} compound;
//                     struct {string id; A_exp exp;} assign;
//                     struct {A_expList exps;} print;
//                    } u;
//             };
//
// struct A_exp_ {enum {A_idExp, A_numExp, A_opExp, A_eseqExp} kind;
//              union {string id;
//                     int num;
//                     struct {A_exp left; A_binop oper; A_exp right;} op;
//                     struct {A_stm stm; A_exp exp;} eseq;
//                    } u;
//             };
int maxargs_exp(A_exp exp) {
    int left;
    int right;
    switch (exp->kind) {
        case A_idExp:
            return 0;
        case A_numExp:
            return 0;
        case A_opExp:
            left = maxargs_exp(exp->u.op.left);
            right = maxargs_exp(exp->u.op.right);
            return left > right ? left : right;
        case A_eseqExp:
            left = maxargs(exp->u.eseq.stm);
            right = maxargs_exp(exp->u.eseq.exp);
            return left > right ? left : right;
    };
    printf("should not arrived 0.\n");
    return -1;
}
int maxargs_explist(A_expList exp_list) {
    int head_cnt;
    int tail_cnt;
    switch(exp_list->kind) {
        case A_pairExpList: 
            head_cnt = maxargs_exp(exp_list->u.pair.head); 
            tail_cnt = maxargs_explist(exp_list->u.pair.tail);
            return head_cnt > tail_cnt ? head_cnt : tail_cnt;
        case A_lastExpList:
            return maxargs_exp(exp_list->u.last);
    }
    printf("should not arrived 1.\n");
    return -1;
}
int count_explist(A_expList exp_list) {
    int count = 1;
    A_expList list = exp_list;
    for (; list->kind != A_lastExpList; list = list->u.pair.tail) {
        ++count;
    }
    return count;
}
int maxargs(A_stm root) {
    int left;
    int right;
    switch(root->kind) {
        case A_compoundStm: 
            left = maxargs(root->u.compound.stm1);
            right = maxargs(root->u.compound.stm2);
            return left > right ? left : right;
        case A_assignStm: 
            return maxargs_exp(root->u.assign.exp);
        case A_printStm: 
            left = count_explist(root->u.print.exps);
            right = maxargs_explist(root->u.print.exps);;
            return left > right ? left : right; 
    };
    printf("should not arrived 2.\n");
    return -1; 
}

int lookup(Table_ t, string key) {
    while (t != NULL) {
        if (strcmp(key, t->id) == 0) {
            return t->value;
        }
        t = t->tail;
    }
    printf("should not arrived 3.\n");
    return -1;
}

Table_ update(Table_ t, string id, int value) {
    return Table(id, value, t);
}

Table_ interpExplist(A_expList exp_list, Table_ t) {
    struct IntAndTable t_ret;
    switch (exp_list->kind) {
        case A_pairExpList:
            t_ret = interpExp(exp_list->u.pair.head, t);
            return interpExplist(exp_list->u.pair.tail, t_ret.t);
        case A_lastExpList:
            t_ret = interpExp(exp_list->u.last, t);
            return t_ret.t; 
    };
}

Table_ interpStm(A_stm s, Table_ t) {
    struct IntAndTable t_ret;
    switch (s->kind) {
        case A_compoundStm:
            return interpStm(s->u.compound.stm2, interpStm(s->u.compound.stm1, t));
        case A_assignStm:
            t_ret = interpExp(s->u.assign.exp, t);
            return update(s->u.assign.id, t_ret.i, t_ret.t);
        case A_printStm:
            return interpExplist(s->u.print.exps, t);
    };
    printf("should not arrived 4.\n");
    return NULL;
}

struct IntAndTable interpExp(A_exp e, Table_ t) {
    struct IntAndTable l_ret;
    struct IntAndTable r_ret;
    Table_ t2;
    switch(e->kind) {
        case A_idExp:
            return int_and_table(lookup(t, e->u.id), t);
        case A_numExp:
            return int_and_table(e->u.num, t);
        case A_opExp:
            l_ret = interpExp(e->u.op.left, t);
            r_ret = interpExp(e->u.op.right, l_ret.t);
            switch (e->u.op.oper) {
                case A_plus:
                    return int_and_table(l_ret.i + r_ret.i, r_ret.t);
                case A_minus:
                    return int_and_table(l_ret.i - r_ret.i, r_ret.t);
                case A_times:
                    return int_and_table(l_ret.i * r_ret.i, r_ret.t);
                case A_div:
                    return int_and_table(l_ret.i / r_ret.i, r_ret.t);
            };
        case A_eseqExp:
            t2 = interpStm(e->u.eseq.stm, t);
            return interpExp(e->u.eseq.exp, t2);
    };
    printf("should not arrived 5.\n");
    return int_and_table(-1, NULL);
}


void interp(A_stm root) {
    interpStm(root, NULL);
}

int main() {
    printf("%d\n", maxargs(prog()));
    return 0;
}
