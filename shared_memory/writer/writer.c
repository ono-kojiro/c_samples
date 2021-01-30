#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <event.h>

#include <getopt.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "common.h"
#include "handler.h"


struct userdata {
	struct event *ev;
	const char *name;
	const char *buf;
};

void sig_int_handler(int fd, short event, void *arg)
{
	fprintf(stdout, "\n");
	event_loopexit(NULL);
}

void read_stdin(int fd, short event, void *arg)
{
	struct userdata *ud = (struct userdata *)arg;
	struct event *ev;
	char buf[256];
	int len;

	int flag = 0;
	char c;

	ev = ud->ev;


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

		fprintf(stderr, "[writer] input '%s'\n", buf);

		if(!strcmp(buf, "exit")){
			event_loopexit(NULL);
		}
#if 0
		else if(!strcmp(buf, "read")){
			fprintf(stderr, "pointer is 0x%p\n", ud);
			fprintf(stderr, "ud->buf is 0x%p\n", ud->buf);
			fprintf(stderr, "shared memory '%s'\n", ud->buf);
			fprintf(stdout, "> ");
		}
#endif
		else {
			sprintf(ud->buf, "%s", buf);
			fprintf(stdout, "> ");
	
		}
	}
}

int main(int argc, char **argv)
{
	int ret = 0;
	int c, index;

	struct event ev;
	struct event sig;

	struct event io_ev;

	struct option options[] = {
		{ "version", no_argument, 0, 'v' },
		{ "keyfile", required_argument, 0, 'k' },
		{ 0, 0, 0, 0 }
	};

	const char *keyfile = NULL;
	int shm_id;
	size_t shm_size = 0x0;
	int shm_flag = 0;

	const char *shm_p = NULL;
	const int id = 33;
	key_t key;

	struct userdata ud;

	while(1){
		c = getopt_long(argc, argv, "vk:", options, &index);
		if(c == -1){
			break;
		}

		switch(c){
			case 'v' :
				break;
			case 'k' :
				keyfile = optarg;
				break;
			default :
				break;
		}
	}

	if(!keyfile){
		fprintf(stderr, "no keyfile option\n");
		ret++;
	}

	if(ret){
		exit(1);
	}
	
	event_init();
	signal_set(&sig, SIGINT, sig_int_handler, NULL);
	signal_add(&sig, NULL);

#if 0
	soc = receiver_socket(host, port, multicast_address);
	if(soc == -1){
		fprintf(stderr, "receiver_socket failed\n");
		exit(1);
	}

	event_set(&ev, soc, EV_READ | EV_PERSIST, handler, &ev);
	err = event_add(&ev, NULL);
	if(err != 0){
		perror("event_add failed");
		close(soc);
		exit(1);
	}
#endif

	key = ftok(keyfile, id);
	if(key == -1){
		fprintf(stderr, "ERROR : ftok error\n");
		exit(1);
	}

	shm_id = shmget(key, shm_size, shm_flag);
	if(shm_id == -1){
		fprintf(stderr, "shmget failed\n");
		exit(1);
	}
	fprintf(stderr, "shm_id : %d\n", shm_id);
	shm_p = (void *)shmat(shm_id, 0, 0);
	if(shm_p == -1){
		fprintf(stderr, "shmat failed\n");
		exit(1);
	}

	sprintf(shm_p, "init");

#if 1
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	fprintf(stderr, "shm_p is %p\n", (void *)shm_p);
	ud.ev = &io_ev;
	ud.buf = shm_p;

	event_set(&io_ev, 0 /* stdin */, EV_READ | EV_PERSIST,
			read_stdin, (void *)&ud /* &io_ev */);
	event_add(&io_ev, NULL);
	fprintf(stdout, "> ");
#endif

	event_dispatch();
	fprintf(stderr, "END\n");

	if(shm_p){
		shmdt(shm_p);
		shm_p = NULL;
	}
#if 0
	shmctl(shm_id, IPC_RMID, NULL);
#endif

	exit(0);
}


