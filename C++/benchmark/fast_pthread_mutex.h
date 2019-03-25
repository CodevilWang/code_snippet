// Copyright 2019 All Rights Reserved.
// Author: taoran07@baidu.com 
#ifndef  UTIL_FAST_PTHREAD_MUTEX_H_
#define  UTIL_FAST_PTHREAD_MUTEX_H_
#include <atomic>
namespace wmlib {
class WmlibFastMutex {
public:
    WmlibFastMutex();
    ~WmlibFastMutex();
    void lock();
    int lock_contended();
    void unlock();
    bool try_lock();
    struct FastMutexInternal {
        std::atomic<unsigned char> locked;
        std::atomic<unsigned char> contended;
        unsigned short padding;
    };
    static constexpr FastMutexInternal FASTMUTEXLOCKED = {{1}, {0}, 0};
    static constexpr FastMutexInternal FASTMUTEXCONTENDED = {{1}, {1}, 0};
private:
    unsigned _futex;
}; 
}

#endif  // UTIL_FAST_PTHREAD_MUTEX_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
