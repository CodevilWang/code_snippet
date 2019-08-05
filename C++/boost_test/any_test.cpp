// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <vector>
#include <type_traits>
#include <boost/any.hpp>
enum GET_TYPE{
    GET_VALUE = 0,
    GET_POINTER = 1,
};
class MyAny {
public:
    template<typename T>
    void set(T p, typename std::enable_if<!std::is_pointer<T>::value>::type* = 0) {
        _any_value = p;
    }
    template<typename T, GET_TYPE GET_VALUE>
    void get(T* p, typename std::enable_if<!std::is_pointer<T>::value>::type* = 0) {
        *p = boost::any_cast<T>(_any_value);
    }
    // template<typename T, typename = std::enable_if<std::is_pointer<std::remove_cv(T)::type>::value>::type>
    template<typename T> //, typename = std::enable_if<std::is_pointer<T>::value>::type>
    bool set(T p, std::function<void(void*)> destr = nullptr, typename std::enable_if<std::is_pointer<T>::value>::type* = 0) {
        printf("in only pointer set\n");
        if (!_any_value.empty()) {
            try {
                boost::any_cast<T>(_any_value);
            } catch(boost::bad_any_cast e) {
                printf("catch bad any cast.\n");
                return false;
            }
            // first cast check
            T pp = nullptr;
            if (!get(&pp)) {
                printf("get pointer failed.\n");
            } else {
                if (_destr) {
                    _destr(pp);
                } else {
                    delete(pp);
                }
            }
        }
        _any_value = p;
        _destr = destr;
        return true;
    }
    template<typename T>
    bool get(T* ret, typename std::enable_if<std::is_pointer<T>::value>::type* = 0) {
        printf("in only pointer get\n");
        *ret = boost::any_cast<T>(_any_value);
        return true;
    }

    template<typename T, GET_TYPE GET_POINTER>
    bool get(T** ret, typename std::enable_if<!std::is_pointer<T>::value>::type* = 0) {
        printf("in only value get\n");
        *ret = boost::any_cast<T>(&_any_value);
        printf("cur %p\n", *ret);
        return true;
    }
private:
    boost::any _any_value;
    std::function<void(void*)> _destr;
};

class TA {
public:
    void work() {
        printf("show class name TA\n");
    }
};
class TB {
public:
    void work() {
        printf("show class name TB\n");
    }
};
void free_dp(void* datap) {
    int* dp = *(int**)(datap);
    printf("in free_dp\n");
    delete(dp);
}
int main() {
    std::vector<boost::any> c;
    c.push_back(TA());
    c.push_back(TB());
    printf("%u\n", c.size());
    TA* tap = boost::any_cast<TA>(&c[0]);
    TA tai = boost::any_cast<TA>(c[0]);
    tap->work();
    tai.work();
    MyAny ma;
    // ma.set(10);
    // printf("%d\n", boost::any_cast<int>(ma.get()));
    int* data = new int(101);
    ma.set(data);
    int* pointer = NULL;
    ma.get(&pointer);
    printf("%d\n", *pointer);
    ma.set(*data);
    int p = 0;
    ma.get<int, GET_VALUE>(&p);
    printf("%d\n", p);
    printf("double pointer check.\n");
    MyAny mb;
    int* pp = new int(102);
    if (!mb.set(&pp)) {
        return 0;
    }
    int** ppp = NULL;
    mb.get(&ppp);
    printf("%d\n", **ppp);

    int* new_dat = new int(100);
    boost::any cur;
    cur = new_dat;
    int* dat = boost::any_cast<int*>(cur);
    printf("%d\n", *dat);

    MyAny mc;
    mc.set(100);
    int mc_dat;
    mc.get<int, GET_VALUE>(&mc_dat);
    printf("%d\n", mc_dat);

    int mc_int = 103;
    mc.set(mc_int);
    int* mc_dat_p = nullptr;
    mc.get<int, GET_POINTER>(&mc_dat_p);
    printf("%d\n", *mc_dat_p);

    TA a_ta;
    mc.set(a_ta);
    TA* a_tc_p = nullptr;
    mc.get<TA, GET_POINTER>(&a_tc_p);
    a_tc_p->work();

    TA b_tc;
    mc.get<TA, GET_VALUE>(&b_tc);
    b_tc.work();
    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
