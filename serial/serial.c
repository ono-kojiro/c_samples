#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <event.h>

#include <getopt.h>

#include <unistd.h>
#include <fcntl.h>

#include <termios.h>

/* for isprint() */
#include <ctype.h>
#include <locale.h>

#include "baudrate.h"

#define CANONICAL_MODE     1
#define NON_CANONICAL_MODE 0

typedef struct {
	int fd_port;
	int canonical_mode;
	int b_echo;
	int debug;
} USERDATA;

int set_stdin_canonical(int enabled)
{
	int fd = 0; // stdin

	struct termios tty;
	if(tcgetattr(fd, &tty) != 0){
		fprintf(stderr, "tcgetattr failed\n");
		return -1;
	}

	if(enabled){
		tty.c_lflag |= ICANON;  // enable canonical processing
		tty.c_lflag |= (ECHO | ECHOE);    // enable echo
	}
	else {
		tty.c_lflag &= ~ICANON; // disable canonical processing
		tty.c_lflag &= ~(ECHO | ECHOE);   // disable echo
	}
	tty.c_cc[VMIN]  = 0;            // read doesn't block
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	if (tcsetattr (fd, TCSANOW, &tty) != 0)
	{
		fprintf(stderr, "error %d from tcsetattr", errno);
		return -1;
	}
	return 0;
}


void sig_int_handler(int fd, short event, void *arg)
{
	int fd_port;
	USERDATA *userdata;
	int debug;
	
	userdata = (USERDATA *)arg;
	fd_port = userdata->fd_port;
	debug = userdata->debug;
	
	if(userdata->canonical_mode){		
		fprintf(stdout, "\n");
		event_loopexit(NULL);
	}
	else{
		if(debug){
			fprintf(stdout, "(write ctrl+c, 0x03)\n");
		}

		write(fd_port, "\x03", 1);
	}
}

void stdin_handler(int fd, short event, void *arg)
{
	char buf[256];
	int len;
	int fd_port;
	int i;
	char c;

	int debug;
	USERDATA *userdata;

	userdata = (USERDATA *)arg;
	fd_port = userdata->fd_port;
	debug = userdata->debug;

	len = read(fd, buf, sizeof(buf) - 1);
	if(len == -1){
		perror("read error");
		return;
	}

	if(len == 0){
		perror("closed");
		event_loopexit(NULL);
		return;
	}

	if(userdata->canonical_mode){
		for(i = 0; i < len; i++){
			if(buf[i] == 0x1b){
				if(debug){
					fprintf(stderr, "(ESC)\n");
				}
				write(fd_port, buf + i, 1);
				set_stdin_canonical(0);
				userdata->canonical_mode = 0;
			}
			else {
				write(fd_port, buf + i, 1);
			}
		}
	}
	else {
		for(i = 0; i < len; i++){
			if(buf[i] == 0x04){
				// EOT, Ctrl+D
				if(debug){
					fprintf(stderr, "(Ctrl+D)\n");
				}
				event_loopexit(NULL);
			}
			
			if(buf[i] == 0x1b){
				// ESC, Ctrl+[
				if(debug){
					fprintf(stderr, "(ESC)\n");
				}
				write(fd_port, buf + i, 1);
				set_stdin_canonical(1);
				userdata->canonical_mode = 1;
			}
			else if(buf[i] == 0x7F){
				/* Backspace */
				write(fd_port, buf + i, 1);
			}
			else {
				//fprintf(stderr, "0x%x", buf[i]);
				write(fd_port, buf + i, 1);
			}
		}
	}
}

void port_handler(int fd, short event, void *arg)
{
	char buf[256];
	int len;
	int i;
	char c;
	int debug;

	USERDATA *userdata;

	userdata = (USERDATA *)arg;

	debug = userdata->debug;

	len = read(fd, buf, sizeof(buf) - 1);
	if(len == -1){
		perror("read error");
	}
	else if(len == 0){
		perror("closed");
	}
	else{
		buf[len] = '\0';
		for(i = 0; i < len; i++){
			c = buf[i];
			if(isprint(c) || c == '\n'){
				fprintf(stderr, "%c", c);
			}
			else if(c == 0x7F){
				/* Backspace */
				fprintf(stderr, "\b \b");
			}
			else if(c == 0x1B){
				/* Delete */
				fprintf(stderr, "\b \b");
			}
			else {
				if(debug){
					fprintf(stderr, "(0x%02x)", c);
				}
			}

			if(userdata->b_echo){
				write(fd, buf + i, sizeof(char));
			}
			
		}
	}
}

int set_port_attributes(int fd, speed_t speed, int parity)
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
	struct event sig_ev;

	struct event io_ev;

	struct option options[] = {
		/* { "host", required_argument, 0, 'h' }, */
		{ "port"    , required_argument, 0, 'p' },
		{ "baudrate"    , required_argument, 0, 'b' },
		{ "echo",     no_argument, 0, 'e' },
		{ "debug",     no_argument, 0, 'd' },
		{ 0, 0, 0, 0 }
	};

	/* const char *host = NULL; */
	const char *port = NULL;
	int baudrate = -1;
	speed_t speed;

	/* int soc; */
	int fd_port;

	int err;
	int b_echo = 0;

	struct termios ts, ots;

	USERDATA userdata;

	memset(&userdata, 0, sizeof(userdata));

	while(1){
		c = getopt_long(
			argc,
			argv, "p:b:ed",
			options, &index);
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
			case 'b' :
				baudrate = atoi(optarg);
				break;
			case 'e' :
				userdata.b_echo = 1;
				break;
			case 'd' :
				userdata.debug = 1;
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

	if(baudrate == -1){
		fprintf(stderr, "no baudrate option\n");
		ret++;
	}
	else {
		speed = get_baudrate_flag(baudrate);
		if(speed == -1){
			fprintf(stderr, "invalid baudrate, %d\n", baudrate);
			ret++;
		}
	}

	if(ret){
		exit(1);
	}

	setlocale(LC_ALL, "C");

	if(tcgetattr(STDIN_FILENO, &ts) != 0){
		fprintf(stderr, "ERROR : %s\n", strerror(errno));
		perror(argv[0]);
		exit(errno);
	}
	
	event_init();
	signal_set(&sig_ev, SIGINT, sig_int_handler, &userdata);
	signal_add(&sig_ev, NULL);

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

	event_set(&ev, fd_port, EV_READ | EV_PERSIST, port_handler, &userdata);
	err = event_add(&ev, NULL);
	if(err != 0){
		perror("event_add");
		close(fd_port);
		exit(1);
	}
	set_port_attributes(fd_port, speed, 0);
	
	set_blocking(fd_port, 0);

	userdata.fd_port = fd_port;

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	set_stdin_canonical(0);

	event_set(&io_ev, 0 /* stdin */, EV_READ | EV_PERSIST,
			stdin_handler, &userdata);
	event_add(&io_ev, NULL);

	event_dispatch();
	fprintf(stderr, "END\n");
	
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts) != 0){
		fprintf(stderr, "ERROR : %s\n", strerror(errno));
		perror(argv[0]);
		exit(errno);
	}
	
	return 0;
}


