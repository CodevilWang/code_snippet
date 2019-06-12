// Copyright 2019 All Rights Reserved.
// Author: taoran07@baidu.com 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>
void child_work(const int& read_fd, const int& write_fd) {
  dup2(write_fd, 1);
  close(read_fd);
  printf("hello in child.\n");
}

int main() {
#ifdef USE_POPEN
  printf("in use popen\n");
  FILE* pp  = popen("./just_print_hello", "r");
  if (!pp) {
    fprintf(stderr, "popen failed. errno %d\n", errno);
    return 1;
  }
  static const size_t dat_len = 1024;
  char data[dat_len];
  while (fgets(data, dat_len, pp) != NULL) {
    printf("paraent %s %d\n", data, strlen(data));
  }
#else
  int fd[2];
  if (pipe(fd) == -1) {
      fprintf(stderr, "pipe failed. errno %d\n", errno);
      return 1;
  }
  // child
  if (fork() == 0) {
      child_work(fd[0], fd[1]);
  } else {
    dup2(fd[0], 0);
    close(fd[1]);
    std::string aline;
    while (std::getline(std::cin, aline)) {
      printf("in parent %s\n", aline.c_str());
    }
  }
#endif
  return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
