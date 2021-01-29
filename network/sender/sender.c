#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include <unistd.h>

#include <event.h>

#include <getopt.h>

#include "common.h"
#include "recv_handler.h"

struct userdata {
	int soc;
	const char *host;
	const char *port;
	const char *multicast_address;
};

void sig_int_handler(int fd, short event, void *arg)
{
	fprintf(stdout, "\n");
	event_loopexit(NULL);
}

void read_stdin(int fd, short event, void *arg)
{
	int ret;

	struct userdata *data = (struct userdata *)arg;
	int soc = data->soc;
	const char *host = data->host;
	const char *port = data->port;
	const char *multicast_address = data->multicast_address;
	
	char buf[256];
	int len;

	int err;

	struct sockaddr_storage dst;
	socklen_t dst_len;

	//fprintf(stderr, "read_stdin called\n");

	if(event & EV_READ){
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

			fprintf(stderr, "[send] : '%s'\n", buf);
			fprintf(stderr, "[dest] %s:%s\n", multicast_address, port);

			err = get_sockaddr_info(multicast_address, port, &dst, &dst_len);
			if(err == -1){
				perror("get_sockaddr_info");
				event_loopexit(NULL);
			}
	
			ret = sendto(soc, buf, strlen(buf), 0,
					(struct sockaddr *)&dst, dst_len);
			if(ret == -1){
				perror("sendto");
				event_loopexit(NULL);
			}
	
			if(!strcmp(buf, "exit")){
				//fprintf(stderr, "exit read_stdin\n");
				event_loopexit(NULL);
			}
			else {
				fprintf(stdout, "> ");
			}
		}
		//event_add(ev, NULL);
	}
}

int main(int argc, char **argv)
{
	int ret = 0;

	int soc;

	struct event ev;
	struct event sig;
	struct event ev_io;

	struct option options[] = {
		{ "host", required_argument, 0, 'h' },
		{ "port"    , required_argument, 0, 'p' },
		{ "multicast-address", required_argument, 0, 'm' },
		{ 0, 0, 0, 0 }
	};

	const char *host = NULL;
	const char *port = NULL;

	const char *multicast_address = NULL;

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
				multicast_address = optarg;
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

	if(multicast_address == NULL){
		fprintf(stderr, "no multicast-address option\n");
		ret++;
	}

	if(ret){
		exit(1);
	}

	event_init();
	signal_set(&sig, SIGINT, sig_int_handler, NULL);
	signal_add(&sig, NULL);

	soc = sender_socket(host, port, multicast_address);
	if(soc == -1){
		fprintf(stderr, "sender_socket failed\n");
		exit(1);
	}

#if 0
	event_set(&ev, soc, EV_READ | EV_PERSIST, recv_handler, &ev);
	err = event_add(&ev, NULL);
	if(err != 0){
		perror("event_add");
		close(soc);
		exit(1);
	}
#endif

	data.soc = soc;
	data.host = host;
	data.port = port;
	data.multicast_address = multicast_address;

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	event_set(&ev_io, 0 /* stdin */, EV_READ | EV_PERSIST,
			read_stdin, (void *)&data);
	err = event_add(&ev_io, NULL);
	if(err != 0){
		perror("event_add");
		close(soc);
		exit(1);
	}
	fprintf(stdout, "> ");

	event_dispatch();
	fprintf(stderr, "END\n");
	return 0;
}


