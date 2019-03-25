// Copyright 2019 All Rights Reserved.
// Author: taoran07@baidu.com 
#ifndef  WMLIB_SYS_CALL_H_
#define  WMLIB_SYS_CALL_H_
#include <unistd.h>
#include <time.h>
#include <syscall.h>
#include <linux/futex.h>

namespace wmlib {

#ifndef FUTEX_PRIVATE_FLAG
#define FUTEX_PRIVATE_FLAG 128
#endif

inline int futex_wait_private(
          void* addr1, int expected, const timespec* timeout) {
    return syscall(SYS_futex, addr1, (FUTEX_WAIT | FUTEX_PRIVATE_FLAG),
                   expected, timeout, NULL, 0);
}

inline int futex_wake_private(void* addr1, int nwake) {
    return syscall(SYS_futex, addr1, (FUTEX_WAKE | FUTEX_PRIVATE_FLAG),
                  nwake, NULL, NULL, 0);
}
};
#endif  // WMLIB_SYS_CALL_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
