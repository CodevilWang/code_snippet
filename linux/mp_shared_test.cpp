/***************************************************************************
 * 
 * Copyright (c) 2019 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file mp_shared_test.cpp
 * @author work(com@baidu.com)
 * @date 2019/05/30 22:43:00
 * @brief 
 *  
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>

void* create_shared_memory(size_t size) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;
  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;
  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, -1, 0);
}

static const int PNUM = 3;
static const int ADDNUM = 100;
int main() {
    pthread_mutex_t shm_mutex;
    const char* parent_message = "hello";  // parent process will write this message
    const char* child_message = "goodbye"; // child process will then write this one
    void* shmem = create_shared_memory(128);
    memcpy(shmem, parent_message, sizeof(parent_message));
    int pid = fork();
    if (pid == 0) {
        printf("Child read: %s\n", shmem);
        memcpy(shmem, child_message, sizeof(child_message));
        printf("Child wrote: %s\n", shmem);
        return 0;
    } else {
        printf("Parent read: %s\n", shmem);
        sleep(1);
        printf("After 1s, parent read: %s\n", shmem);
    }

    int err;
    pthread_mutexattr_t attr;
    if (pthread_mutexattr_init(&attr)) {
        fprintf(stderr, "pthread_mutexattr_init failed.\n");
        return -1;
    }

    if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED) != 0) {
        fprintf(stderr, "pthread_mutexattr_init failed.\n");
        return -1;
    }

    if (pthread_mutex_init(&shm_mutex, &attr) != 0) {
        fprintf(stderr, "pthread_mutexattr_init failed.\n");
        return -1;
    }
    
    int fork_ret = 0;
    pid_t wpid;
    int status = 0;
    int* data = (int*)(shmem);
    data[0] = 0;
    data[1] = 0;
    
    for (int i = 0; i < PNUM; ++i) {
        fork_ret = fork();
        if (fork_ret == 0) {
            break;
        }
    }

    if (fork_ret == 0) {
        for (int i = 0; i < ADDNUM; ++i) {
            pthread_mutex_lock(&shm_mutex);
            int* data = (int*)(shmem);
            ++data[0];
            ++data[1];
            pthread_mutex_unlock(&shm_mutex);
        }
        return 0;
    }
    while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes 

    printf("after all wait %d\t%d\n", data[0], data[1]);
    // err = pthread_mutexattr_destroy(&attr); if (err) return err;
    // err = pthread_mutex_lock(&shm_mutex); if (err) return err;
    // err = pthread_mutex_unlock(&shm_mutex); if (err) return err;
    // err = pthread_mutex_destroy(&shm_mutex); if (err) return err;
 
    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
