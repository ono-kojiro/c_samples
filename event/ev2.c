#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include <unistd.h>

#include <event2/event.h>

#include <getopt.h>

void sig_int_handler(int fd, short event, void *arg)
{
	struct event_base *base = (struct event_base *)arg;
	fprintf(stdout, "sig_int_handler\n");
	event_base_loopbreak(base);
}

void read_stdin(int fd, short event, void *arg)
{
	int ret;
	
	char buf[256];
	int num;
	
	struct event_base *base = (struct event_base *)arg;

	buf[0] = '\0';
	num = read(fd, buf, sizeof(buf) - 1);
	if(num == -1){
		perror("read error");
	}
	else{
		if(num > 0){
			if(buf[num - 1] == '\n'){
				buf[num - 1] = '\0';
			}
			else{
				buf[num] = '\0';
			}
		}

		fprintf(stderr, "DEBUG : '%s'\n", buf);

		if(!strcmp(buf, "exit")){
			event_base_loopbreak(base);
		}
		else {
			fprintf(stdout, "> ");
		}
	}
}

int main(int argc, char **argv)
{
	int ret = 0;
	
	int c, index;
	struct option options[] = {
		{ "host", required_argument, 0, 'h' },
		{ "port"    , required_argument, 0, 'p' },
		{ 0, 0, 0, 0 }
	};

	struct event_base *base;

	struct event *ev_sig;
	struct event *ev_io;

	int err;

	while(1){
		c = getopt_long(argc, argv, "h:p:", options, &index);
		if(c == -1){
			break;
		}

		switch(c){
			case 'h' :
				break;
			case 'p' :
				break;
			default :
				break;
		}
	}

#if 0
	if(host == NULL){
		fprintf(stderr, "no host option\n");
		ret++;
	}

	if(port == NULL){
		fprintf(stderr, "no port option\n");
		ret++;
	}
#endif

	if(ret){
		exit(1);
	}
	
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	base = event_base_new();
	
	ev_sig = evsignal_new(
		base, SIGINT, sig_int_handler, base);
	err = event_add(ev_sig, NULL);
	if(err != 0){
		perror("event_add");
		exit(1);
	}

	ev_io = event_new(base, 0 /* stdin */, EV_READ|EV_PERSIST,
		read_stdin, base);

	err = event_add(ev_io, NULL);
	if(err != 0){
		perror("event_add");
		exit(1);
	}
	fprintf(stdout, "> ");

	event_base_dispatch(base);
	fprintf(stderr, "END\n");

	event_base_free(base);
	return 0;
}


