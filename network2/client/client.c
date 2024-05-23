#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include <unistd.h>

#include <event.h>

#include <getopt.h>

#include "common.h"

struct userdata {
  int soc;
};

void sig_int_handler(int fd, short event, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
	fprintf(stdout, "\n");
	event_base_loopexit(base, NULL);
}

void stdin_handler(int fd, short event, void *arg)
{
	int ret;
    struct userdata *ud = (struct userdata *)arg;
	
	char buf[256];
	int len;

    int soc = ud->soc;

	len = read(fd, buf, sizeof(buf) - 1);
	if(len == -1){
		perror("read error");
	}
	else if(len == 0){
        // Ctrl+D
	}
	else{
		fprintf(stderr, "send : %s", buf);

		ret = send(soc, buf, strlen(buf), 0);
		if(ret == -1){
			perror("send");
			event_loopexit(NULL);
		}

		fprintf(stdout, "> ");
	}
}

size_t mystrlcat(char *dst, const char *src, size_t size)
{
    const char *ps;
    char *pd, *pde;
    size_t dlen, lest;
    
    for (pd = dst, lest = size; *pd != '\0' && lest !=0; pd++, lest--);
    dlen = pd - dst;
    if (size - dlen == 0) {
        return (dlen + strlen(src));
    }
    pde = dst + size - 1;
    for (ps = src; *ps != '\0' && pd < pde; pd++, ps++) {
        *pd = *ps;
    }
    for (; pd <= pde; pd++) {
        *pd = '\0';
    }
    while (*ps++);
    return (dlen + (ps - src - 1));
}

/* 送受信ハンドラ */
void recv_callback(struct bufferevent *bev, void *ctx)
{
    struct evbuffer *in, *out;
    char *line;
    size_t n;
    
    in  = bufferevent_get_input(bev);
    out = bufferevent_get_output(bev);
    
    while(1){
        line = evbuffer_readln(in, &n, EVBUFFER_EOL_LF);
        if(!line){
            break;
        }

        fprintf(stderr, "rcv: %*s\n", (int)n, line);
        free(line);
    }
}

int client_socket(const char *host, const char *port)
{
	int soc;
	int err;

	struct addrinfo *info;

	{
		struct addrinfo hints;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;

		err = getaddrinfo(host, port, &hints, &info);
		if(err != 0){
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
			exit(EXIT_FAILURE);
		}
	}

    {
	    char host[NI_MAXHOST];
	    char service[NI_MAXSERV];

	    err = getnameinfo(
			info->ai_addr,info->ai_addrlen,
			host,    NI_MAXHOST,
			service, NI_MAXSERV,
			NI_NUMERICHOST | NI_NUMERICSERV);
	    if(err != 0){
		    fprintf(stderr, "getnameinfo():%s\n", gai_strerror(err));
		    freeaddrinfo(info);
			exit(EXIT_FAILURE);
	    }

	    fprintf(stderr, "host = %s, service = %s\n", host, service);
    }

    {
        struct addrinfo *rp;
        for(rp = info; rp != NULL; rp = rp->ai_next){
	        soc = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	        if(soc == -1){
                continue;
            }

            err = connect(soc, rp->ai_addr, rp->ai_addrlen);
            if(err != -1){
                // success
                break;
            }

            // failed
            close(soc);
	    }

        if(rp == NULL){
            fprintf(stderr, "Could not connect\n");
            exit(EXIT_FAILURE);
        }
    }

	freeaddrinfo(info);
	return soc;
}


int main(int argc, char **argv)
{
	int ret = 0;

	int soc;

    struct event_base *base;
	struct event *ev_rcv;
	struct event *ev_int;
	struct event *ev_io;

    struct userdata ud;

	struct option options[] = {
		{ "host", required_argument, 0, 'h' },
		{ "port", required_argument, 0, 'p' },
		{ 0, 0, 0, 0 }
	};

	const char *host = NULL;
	const char *port = NULL;

	int err;

	int c, index;
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
	ev_int = evsignal_new(base, SIGINT, sig_int_handler, (void *)base);
    event_add(ev_int, NULL);

	soc = client_socket(host, port);
	if(soc == -1){
		fprintf(stderr, "client_socket failed\n");
		exit(1);
	}

    evutil_make_socket_nonblocking(soc);
    {
        struct bufferevent *bev;
        bev = bufferevent_socket_new(base, soc, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, recv_callback, NULL, NULL, NULL);
        bufferevent_enable(bev, EV_READ);
    }

    ud.soc = soc;

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
    ev_io = event_new(base,
        0, // stdin
        EV_READ|EV_PERSIST,
        stdin_handler,
        (void *)&ud
    );
	err = event_add(ev_io, NULL);
	if(err != 0){
		perror("event_add");
		close(soc);
		exit(1);
	}
	fprintf(stdout, "> ");

	event_base_dispatch(base);
	fprintf(stderr, "END\n");

    event_base_free(base);
	exit(0);
}


