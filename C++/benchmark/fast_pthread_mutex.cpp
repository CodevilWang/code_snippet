// Copyright 2019 All Rights Reserved.
// Author: taoran07@baidu.com 
#include "fast_pthread_mutex.h" 
#include <stdio.h>
#include <errno.h>
#include "sys_call.h"
namespace wmlib {
constexpr WmlibFastMutex::FastMutexInternal WmlibFastMutex::FASTMUTEXLOCKED;
constexpr WmlibFastMutex::FastMutexInternal WmlibFastMutex::FASTMUTEXCONTENDED;
static const unsigned V_FASTLOCKED = *(const unsigned*)(&WmlibFastMutex::FASTMUTEXLOCKED);
static const unsigned V_FASTCONTENDED = *(const unsigned*)(&WmlibFastMutex::FASTMUTEXCONTENDED);
WmlibFastMutex::WmlibFastMutex() : _futex(0) {}
WmlibFastMutex::~WmlibFastMutex() {}
int WmlibFastMutex::lock_contended() {
    std::atomic<unsigned>* m_internal = (std::atomic<unsigned>*)(&_futex);
    while (m_internal->exchange(V_FASTCONTENDED) & V_FASTLOCKED) {
        if (futex_wait_private(&_futex, V_FASTCONTENDED, NULL) < 0 && errno != EWOULDBLOCK) {
            return errno;
        }
    }
    return 0;
}
void WmlibFastMutex::lock() {
    WmlibFastMutex::FastMutexInternal* m_internal = (WmlibFastMutex::FastMutexInternal*)(&_futex);
    if (m_internal->locked.exchange(1, std::memory_order_acquire)) {
        (void)lock_contended();
    }
}
void WmlibFastMutex::unlock() {
    std::atomic<unsigned>* whole = (std::atomic<unsigned>*)(&_futex);
    unsigned prev = whole->exchange(0, std::memory_order_release);
    WmlibFastMutex::FastMutexInternal* fmi = (WmlibFastMutex::FastMutexInternal*)(&prev);
    if (fmi->contended.load(std::memory_order_relaxed)) {
        futex_wake_private(&_futex, 1);
    }
}
bool WmlibFastMutex::try_lock() {
    WmlibFastMutex::FastMutexInternal* m_internal = (WmlibFastMutex::FastMutexInternal*)(&_futex);
    if (!m_internal->locked.exchange(1, std::memory_order_acquire)) {
        return true;
    }
    return false;
}
};
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
