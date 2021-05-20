#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <event.h>

#include <getopt.h>

#include <unistd.h>
#include <fcntl.h>

#include <termios.h>

typedef struct {
	int fd_port;
} USERDATA;

void sig_int_handler(int fd, short event, void *arg)
{
	fprintf(stdout, "\n");
	event_loopexit(NULL);
}

void stdin_handler(int fd, short event, void *arg)
{
	struct event *ev = arg;
	char buf[256];
	int len;

	USERDATA *userdata = (USERDATA *)arg;

	int fd_port = userdata->fd_port;


	len = read(fd, buf, sizeof(buf) - 1);
	if(len == -1){
		perror("read error");
	}
	else if(len == 0){
		perror("closed");
		event_loopexit(NULL);
	}
	else{
		if(!strcmp(buf, "exit")){
			event_loopexit(NULL);
		}
		else {
			write(fd_port, buf, len);
		}
	}
}

void port_handler(int fd, short event, void *arg)
{
	struct event *ev = arg;
	char buf[256];
	int len;

	len = read(fd, buf, sizeof(buf) - 1);
	if(len == -1){
		perror("read error");
	}
	else if(len == 0){
		perror("closed");
	}
	else{
		buf[len] = '\0';
		fprintf(stderr, "%s", buf);
	}
}

int set_port_attributes(int fd, int speed, int parity)
{
	struct termios tty;
	if(tcgetattr(fd, &tty) != 0){
		fprintf(stderr, "tcgetattr failed\n");
		return -1;
	}

	cfsetospeed(&tty, speed);
	cfsetispeed(&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;         // disable break processing
	tty.c_lflag = 0;                // no signaling chars, no echo,
									// no canonical processing
	tty.c_oflag = 0;                // no remapping, no delays
	tty.c_cc[VMIN]  = 0;            // read doesn't block
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
									// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr (fd, TCSANOW, &tty) != 0)
	{
		fprintf(stderr, "error %d from tcsetattr", errno);
		return -1;
	}
	return 0;
}

void set_blocking (int fd, int should_block)
{
	struct termios tty;
	memset (&tty, 0, sizeof tty);
	if (tcgetattr (fd, &tty) != 0)
	{
		fprintf(stderr, "error %d from tggetattr", errno);
		return;
	}

	tty.c_cc[VMIN]  = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
	if (tcsetattr (fd, TCSANOW, &tty) != 0){
		fprintf(stderr, "error %d setting term attributes", errno);
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
		/* { "host", required_argument, 0, 'h' }, */
		{ "port"    , required_argument, 0, 'p' },
		{ 0, 0, 0, 0 }
	};

	/* const char *host = NULL; */
	const char *port = NULL;

	/* int soc; */
	int fd_port;

	int err;

	USERDATA userdata;

	while(1){
		c = getopt_long(argc, argv, "p:", options, &index);
		if(c == -1){
			break;
		}

		switch(c){
			/*
			case 'h' :
				host = optarg;
				break;
			*/
			case 'p' :
				port = optarg;
				break;
			default :
				break;
		}
	}

	/*
	if(host == NULL){
		fprintf(stderr, "no host option\n");
		ret++;
	}
	*/

	
	if(port == NULL){
		fprintf(stderr, "no port option\n");
		ret++;
	}

	if(ret){
		exit(1);
	}
	
	event_init();
	signal_set(&sig, SIGINT, sig_int_handler, NULL);
	signal_add(&sig, NULL);

	/*
	soc = server_socket(host, port);
	if(soc == -1){
		fprintf(stderr, "server_socket failed\n");
		exit(1);
	}
	*/
	fd_port = open(port, O_RDWR | O_NOCTTY | O_SYNC);
	if(fd_port < 0){
		fprintf(stderr, "can not open %s\n", port);
		exit(1);
	}

	event_set(&ev, fd_port, EV_READ | EV_PERSIST, port_handler, &ev);
	err = event_add(&ev, NULL);
	if(err != 0){
		perror("event_add");
		close(fd_port);
		exit(1);
	}
	set_port_attributes(fd_port, B115200, 0);
	set_blocking(fd_port, 0);

	userdata.fd_port = fd_port;


#if 1
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	event_set(&io_ev, 0 /* stdin */, EV_READ | EV_PERSIST,
			stdin_handler, &userdata);
	event_add(&io_ev, NULL);
#endif

	event_dispatch();
	fprintf(stderr, "END\n");
	return 0;
}


