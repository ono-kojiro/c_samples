#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <event.h>

#include <getopt.h>

#include <unistd.h>

#include "common.h"

#define MAX_LINE 16384

void sig_int_handler(int fd, short event, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
	fprintf(stdout, "\n");
	event_base_loopexit(base, NULL);
}

void read_stdin(int fd, short event, void *arg)
{
	struct event *ev = arg;
	char buf[256];
	int len;

	//fprintf(stderr, "read_stdin called\n");

	len = read(fd, buf, sizeof(buf) - 1);
	if(len == -1){
		perror("read error");
	}
	else if(len == 0){
		perror("closed");
	}
	else{
		if(buf[len - 1] == '\n'){
			buf[len - 1] = '\0';
		}
		else{
			buf[len] = '\0';
		}

		//fprintf(stderr, "DEBUG : '%s'\n", buf);

		if(!strcmp(buf, "exit")){
			//fprintf(stderr, "exit read_stdin\n");
			event_loopexit(NULL);
		}
		else {
			fprintf(stdout, "> ");
	
		}
	}
}

void read_callback(struct bufferevent *bev, void *ctx)
{
    struct evbuffer *in, *out;
    char *line;
    size_t n;
    int i;

    in  = bufferevent_get_input(bev);
    out = bufferevent_get_output(bev);

    while(1){
        line = evbuffer_readln(in, &n, EVBUFFER_EOL_LF);
        if(!line){
            break;
        }
        fprintf(stderr, "rcv: %s\n", line);

        evbuffer_add(out, line, n);
        evbuffer_add(out, "\n", 1);
        free(line);
    }

    if(evbuffer_get_length(in) >= MAX_LINE){
        char buf[1024];
        while(evbuffer_get_length(in)){
            int n = evbuffer_remove(in, buf, sizeof(buf));
            evbuffer_add(out, buf, n);
        }
        evbuffer_add(out, "\n", 1);
    }
}

void error_callback(struct bufferevent *bev, short error, void *ctx)
{
    if(error & BEV_EVENT_EOF){
        fprintf(stderr, "BEV_EVENT_EOF\n");
    }
    else if(error & BEV_EVENT_ERROR){
        fprintf(stderr, "BEV_EVENT_ERROR\n");

    }
    else if(error & BEV_EVENT_TIMEOUT){
        fprintf(stderr, "BEV_EVENT_TIMEOUT\n");
    }
    else {

    }
    bufferevent_free(bev);
}

void do_accept(int soc, short event, void *arg)
{
    struct event_base *base = (struct event_base *)arg;

	int acc;
	struct sockaddr_storage storage;
	socklen_t len = sizeof(storage);

    acc = accept(soc, (struct sockaddr *)&storage, &len);
	if(acc < 0){
		perror("accept");
	}
    else if(acc > FD_SETSIZE){
        close(acc);
    }
	else{
        struct bufferevent *bev;

        {
            char addr[NI_MAXHOST];
            char port[NI_MAXSERV];
            getnameinfo(
                (struct sockaddr *)&storage,
                len,
                addr, sizeof(addr),
                port, sizeof(port),
                NI_NUMERICHOST | NI_NUMERICSERV);
            fprintf(stderr, "accept:%s:%s\n", addr, port);
        }
        evutil_make_socket_nonblocking(acc);
        bev = bufferevent_socket_new(base, acc, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, read_callback, NULL, error_callback, &acc);
        bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
        bufferevent_enable(bev, EV_READ);
	}
}

int main(int argc, char **argv)
{
	int ret = 0;
	int c, index;

    struct event_base *base;
	struct event *ev_io;
	struct event *ev_int;
	struct event *ev_acpt;

	struct option options[] = {
		{ "host", required_argument, 0, 'h' },
		{ "port"    , required_argument, 0, 'p' },
		{ 0, 0, 0, 0 }
	};

	const char *host = NULL;
	const char *port = NULL;

	int soc;

	int err;

	while(1){
		c = getopt_long(argc, argv, "h:p:", options, &index);
		if(c == -1){
			break;
		}

		switch(c){
			case 'h' :
				host = optarg;
				break;
			case 'p' :
				port = optarg;
				break;
			default :
				break;
		}
	}

	if(host == NULL){
		fprintf(stderr, "no host option\n");
		ret++;
	}
	
	if(port == NULL){
		fprintf(stderr, "no port option\n");
		ret++;
	}

	if(ret){
		exit(1);
	}

	
	base = event_base_new();
	ev_int = evsignal_new(base, SIGINT, sig_int_handler, base);
    event_add(ev_int, NULL);

	soc = server_socket(host, port);
	if(soc == -1){
		fprintf(stderr, "server_socket failed\n");
		exit(1);
	}

	ev_acpt = event_new(base, soc, EV_READ | EV_PERSIST, do_accept, base);
	err = event_add(ev_acpt, NULL);
	if(err != 0){
		perror("event_add");
		close(soc);
		exit(1);
	}

#if 1
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	ev_io = event_new(base, 0 /* stdin */, EV_READ | EV_PERSIST,
			read_stdin, base);
	event_add(ev_io, NULL);
	fprintf(stdout, "> ");
#endif

	event_base_dispatch(base);
	fprintf(stderr, "END\n");
    event_base_free(base);
	return 0;
}


