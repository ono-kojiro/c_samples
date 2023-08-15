#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include <unistd.h>

#include <event.h>

#include <getopt.h>

//#include "common.h"
//#include "recv_handler.h"

struct userdata {
	int soc;
	const char *host;
	const char *port;
	const char *multicast_addr;
	struct addrinfo *info;
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

	struct userdata *data = (struct userdata *)arg;
	int soc = data->soc;
	const char *host = data->host;
	const char *port = data->port;
	const char *multicast_addr = data->multicast_addr;
    struct addrinfo *info = data->info;
	
	char buf[256];
	int len;

	int err;

	struct sockaddr_storage dst;
	socklen_t dst_len;

	if(event & EV_READ){
		len = read(fd, buf, sizeof(buf) - 1);
		if(len == -1){
			perror("read error");
		}
		else if(len == 0){
			// Ctrl+D
		}
		else{
			ret = sendto(soc, buf, len, 0,
					info->ai_addr, info->ai_addrlen);
			if(ret == -1){
				perror("sendto");
				event_loopexit(NULL);
			}
	
			fprintf(stdout, "> ");
		}
	}
}

int get_addr_info(const char *host, const char *port,
            struct addrinfo **info)
{
    int err;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    err = getaddrinfo(host, port, &hints, info);
    if(err != 0){
        fprintf(stderr, "getaddrinfo():%s\n", gai_strerror(err));
        return -1;
    }

    return 0;
}

int print_name_info(struct addrinfo *info)
{
    int err;
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    err = getnameinfo(
            info->ai_addr, info->ai_addrlen,
            host,    NI_MAXHOST,
            service, NI_MAXSERV,
            NI_NUMERICHOST | NI_NUMERICSERV);

    if(err != 0){
        fprintf(stderr, "getnameinfo():%s\n", gai_strerror(err));
        exit(1);
    }

    fprintf(stderr, "host=%s, service=%s\n", host, service);

    return 0;
}

int main(int argc, char **argv)
{
	int ret = 0;

	int soc;

    struct event_base *base;
	struct event *ev_rcv;
    struct event *ev_int;
	struct event *ev_io;

	struct option options[] = {
		{ "host", required_argument, 0, 'h' },
		{ "port"    , required_argument, 0, 'p' },
		{ "multicast-address", required_argument, 0, 'm' },
		{ 0, 0, 0, 0 }
	};

	const char *host = NULL;
	const char *port = NULL;

	const char *multicast_addr = NULL;
    struct addrinfo *info;
	unsigned char multicast_ttl = 64;
	unsigned char multicast_loopback = 1;

	struct userdata data;

	int err;

	int c, index;
	while(1){
		c = getopt_long(argc, argv, "h:p:m:", options, &index);
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
			case 'm' :
				multicast_addr = optarg;
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

#if 0
	if(multicast_addr == NULL){
		fprintf(stderr, "no multicast-address option\n");
		ret++;
	}
#endif

	if(ret){
		exit(1);
	}

	base = event_base_new();
	ev_int = evsignal_new(base, SIGINT, sig_int_handler, (void *)base);
	signal_add(ev_int, NULL);

    ret = get_addr_info(host, port, &info);
    if(ret != 0){
        exit(1);
    }
    print_name_info(info);

    data.info = info;

    soc = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if(soc == -1){
		perror("socket");
		freeaddrinfo(info);
		return -1;
	}
	
    err = setsockopt(soc, IPPROTO_IP, IP_MULTICAST_TTL,
					&multicast_ttl, sizeof(multicast_ttl));
	if(err == -1){
		perror("setsockopt");
		freeaddrinfo(info);
		close(soc);
		return -1;
	}

	err = setsockopt(soc, IPPROTO_IP, IP_MULTICAST_LOOP,
					&multicast_loopback, sizeof(multicast_loopback));
	if(err == -1){
		perror("setsockopt");
		freeaddrinfo(info);
		close(soc);
		return -1;
	}


	data.soc = soc;
	data.host = host;
	data.port = port;
	data.multicast_addr = multicast_addr;
	
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	ev_io = event_new(base,
                0 /* stdin */,
                EV_READ | EV_PERSIST,
			    stdin_handler, (void *)&data);
	err = event_add(ev_io, NULL);
	if(err != 0){
		perror("event_add");
		close(soc);
        event_base_free(base);
		exit(1);
	}
	fprintf(stdout, "> ");

	event_base_dispatch(base);
	fprintf(stderr, "END\n");
    event_base_free(base);
    freeaddrinfo(info);
	return 0;
}


