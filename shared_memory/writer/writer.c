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

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "common.h"
#include "handler.h"

struct userdata {
	struct event *ev;
	const char *name;
	char *buf;
	int fd_shm;
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

	struct event shm_evn;
	int fd;
	mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH;
	struct stat st;
	unsigned char *buf;

	struct option options[] = {
		{ "version", no_argument, 0, 'v' },
		{ "keyfile", required_argument, 0, 'k' },
		{ 0, 0, 0, 0 }
	};

	struct userdata ud;

	while(1){
		c = getopt_long(argc, argv, "vk:", options, &index);
		if(c == -1){
			break;
		}

		switch(c){
			case 'v' :
				break;
			default :
				break;
		}
	}

	if(ret){
		exit(1);
	}
	
	event_init();
	signal_set(&sig, SIGINT, sig_int_handler, NULL);
	signal_add(&sig, NULL);

#if 1
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	fd = shm_open("test", O_RDWR | O_CREAT, 0755);
	if(fd == -1){
		fprintf(stderr, "shm_open failed\n");
		exit(1);
	}

	ftruncate(fd, 1024);
	fstat(fd, &st);
	buf = mmap(NULL,
			st.st_size,
			PROT_READ|PROT_WRITE,
			MAP_SHARED,
			fd,
			0);

	ud.fd_shm = fd;
	ud.buf = buf;

	ud.ev = &io_ev;

	event_set(&io_ev, 0 /* stdin */, EV_READ | EV_PERSIST,
			read_stdin, (void *)&ud /* &io_ev */);
	event_add(&io_ev, NULL);
	fprintf(stdout, "> ");
#endif

	event_dispatch();
	fprintf(stderr, "END\n");

	close(fd);
	shm_unlink("test");

	exit(0);
}


