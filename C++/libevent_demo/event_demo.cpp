// code from libevent tutorial
/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For fcntl */
#include <fcntl.h>

#include <event2/event.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void cb_func(evutil_socket_t fd, short what, void* args) {
    const char* data = (const char*)args;
    printf("Got an event on socket %d:%s%s%s%s [%s]\n", int(fd),
            (what & EV_TIMEOUT) ? "timeout" : "",
            (what & EV_READ) ? "read" : "",
            (what & EV_WRITE) ? "write": "",
            (what & EV_SIGNAL) ? "signal" : "",
            data);
    if (what & EV_READ) {
        char t_data[128];
        int ret = read(fd, t_data, 128);
        printf("readed [%d] data[%s]\n", ret, t_data);
    }
}

void cb_func2(evutil_socket_t fd, short what, void* args) {
    struct event* self_ev = (struct event*) args;
    static int num = 0;
    if (num > 10) {
        printf("deleting self event.\n");
        event_del(self_ev);
    }
    ++num;
}

int main(int c, char **v)
{
    struct event *ev1, *ev2;
    struct timeval five_seconds = {5, 0};
    struct event_base* base = event_base_new();
    ev1 = event_new(base, 0, EV_TIMEOUT | EV_READ | EV_PERSIST, cb_func, (char*)"Reading Event");
    // ev2 = event_new(base, fd2, EV_WRITE, cb_func, "Writing Event");
    event_add(ev1, &five_seconds);
    ev2 = event_new(base, -1, EV_PERSIST, cb_func2, event_self_cbarg());
    struct timeval one_seconds = {1, 0};
    event_add(ev2, &one_seconds);
    event_base_dispatch(base);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
