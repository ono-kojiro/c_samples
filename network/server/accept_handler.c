#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include <event.h>

#include "accept_handler.h"
#include "recv_handler.h"


void accept_handler(int soc, short event, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
	int err;

	char addr[NI_MAXHOST];
	char port[NI_MAXSERV];
	int acc;
	struct sockaddr_storage storage;
	socklen_t len;

	struct event *ev;

    acc = accept(soc, (struct sockaddr *)&storage, &len);
	if(acc < 0){
		perror("accept");
	}
    else if(acc > FD_SETSIZE){
        close(fd);
    }
	else{
        struct bufferevent *bev;
        evutil_make_socket_nonblocking(acc);
        bev = bufferevent_socket_new(base, acc, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, read_callback, NULL, error_callback, NULL);
        bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
        bufferevent_enable(bev, EV_READ);
	}
}

