#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
int main() {
    int rc = -1;
    int fd = open("/tmp/foobar.txt", O_RDWR | O_CREAT, 0777);
    printf("current fd[%d]\n", fd);
    if (fd == -1) {
        printf("current open failed. errno [%d]\n", errno);
    }
    rc = flock(fd, LOCK_EX);
    printf("lock fd[%d] re[%d]\n", fd, rc);
    rc = flock(fd, LOCK_EX);
    printf("lock fd[%d] re[%d]\n", fd, rc);
    int ret = fork();
    if (ret < 0) {
        printf("process fork error. errno[%d]\n", errno);
        return -1;
    } else if (ret == 0) {
        rc = flock(fd, LOCK_EX);
        printf("lock from sub process ret %d fd[%d]\n", rc, fd);
        return 0;
    } else { 
        rc = flock(fd, LOCK_EX);
        printf("lock from parent process ret %d fd[%d]\n", rc, fd);
        pid_t pw = wait(NULL);
        printf("I catch a child process pid[%d]\n", pw);
        return 0;
    }
    return 0;
}
