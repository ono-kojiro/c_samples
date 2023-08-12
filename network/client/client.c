#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include <unistd.h>

#include <event.h>

#include <getopt.h>

#include "common.h"
#include "recv_handler.h"

void sig_int_handler(int fd, short event, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
	fprintf(stdout, "\n");
	event_base_loopexit(base, NULL);
}

void read_stdin(int fd, short event, void *arg)
{
	int ret;
	int soc = (int)arg;
	
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
#if 0
		if(buf[len - 1] == '\n'){
			buf[len - 1] = '\0';
		}
		else{
			buf[len] = '\0';
		}
#endif
		//fprintf(stderr, "DEBUG : '%s'\n", buf);

		ret = send(soc, buf, strlen(buf), 0);
		if(ret == -1){
			perror("send");
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

    ev_rcv = event_new(base, soc, EV_READ|EV_PERSIST, recv_handler, NULL);
 
	err = event_add(ev_rcv, NULL);
	if(err != 0){
		perror("event_add");
		close(soc);
		exit(1);
	}

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
    ev_io = event_new(base,
        0, // stdin
        EV_READ|EV_PERSIST,
        read_stdin,
        (void *)soc
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


