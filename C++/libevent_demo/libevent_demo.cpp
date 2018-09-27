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

int main(int c, char **v)
{
    const char** methods = event_get_supported_methods();
    printf("Starting Libevent %s. Available methods are:\n", event_get_version());
    for (int i = 0; methods[i] != NULL; ++i) {
        printf("	%s\n", methods[i]);
    }
    struct event_base* base = event_base_new();
    int f = event_base_get_features(base);
    if (f & EV_FEATURE_ET) {
        printf("supprted ev_feature_et\n");
    }
    if (f & EV_FEATURE_O1) {
        printf("supprted ev_feature_o1\n");
    }
    if (f & EV_FEATURE_FDS) {
        printf("supprted ev_feature_fds\n");
    }
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
