#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <event.h>

#include <getopt.h>

#include <unistd.h>

//#include "common.h"
//#include "recv_handler.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

size_t
mystrlcat(char *dst, const char *src, size_t size)
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


int receiver_socket(const char *host, const char *port,
				const char *multicast_address)
{
	int soc;

	int err;
	struct addrinfo *info;

	char host_buf[NI_MAXHOST];
	char serv_buf[NI_MAXSERV];

	int opt;
	socklen_t opt_len;

	struct ip_mreq mreq;

	{
		struct addrinfo hints;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		//hints.ai_socktype = SOCK_STREAM;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_flags = AI_PASSIVE;

		//err = getaddrinfo(host, port, &hints, &info);
		err = getaddrinfo(NULL, port, &hints, &info);
		if(err != 0){
			fprintf(stderr, "getaddrinfo():%s\n", gai_strerror(err));
			return -1;
		}
	}

	err = getnameinfo(
			info->ai_addr,info->ai_addrlen,
			host_buf, sizeof(host_buf),
			serv_buf, sizeof(serv_buf),
			NI_NUMERICHOST | NI_NUMERICSERV);
	if(err != 0){
		fprintf(stderr, "getnameinfo():%s\n", gai_strerror(err));
		freeaddrinfo(info);
		return -1;
	}

	fprintf(stderr, "addr = %s, port = %s\n", host_buf, serv_buf);

	soc = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if(soc == -1){
		perror("socket");
		freeaddrinfo(info);
		return -1;
	}

	opt = 1;
	opt_len = sizeof(opt);
	err = setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &opt, opt_len);
	if(err == -1){
		perror("setsockopt");
		close(soc);
		freeaddrinfo(info);
		return -1;
	}

	err = bind(soc, info->ai_addr, info->ai_addrlen);
	if(err == -1){
		perror("bind");
		close(soc);
		freeaddrinfo(info);
		return -1;
	}

	if(multicast_address){
		fprintf(stderr,"mutlcast_address is %s\n", multicast_address);
		/* join multicast group */
		inet_pton(AF_INET, multicast_address, &mreq.imr_multiaddr);
		inet_pton(AF_INET, host, &mreq.imr_interface);
		err = setsockopt(soc, IPPROTO_IP, IP_ADD_MEMBERSHIP,
				&mreq, sizeof(mreq));
		if(err == -1){
			fprintf(stderr, "ERROR : %s(%d)\n", __FILE__, __LINE__ );
			perror("setsockopt");
			close(soc);
			freeaddrinfo(info);
			return -1;
		}
	}
	
	freeaddrinfo(info);

	return soc;
}


/* 送受信ハンドラ */
void recv_handler(int soc, short event, void *arg)
{
    char buf[512], *ptr;
    ssize_t len;
	struct sockaddr_storage info;
	socklen_t info_len;

	char addr_buf[NI_MAXHOST];
	char port_buf[NI_MAXSERV];

    /* event_set()の第５引数のデータをargで受け取れる */
    struct event *ev = (struct event*) arg;

    /* イベントのタイプが読み込み可能だった */
    if (event & EV_READ) {
        /* 受信 */
		info_len = sizeof(info);
        if ((len = recvfrom(soc, buf, sizeof(buf), 0,
						(struct sockaddr *)&info, &info_len)) == -1) {
            /* エラー */
            perror("recvfrom");
	    (void) event_del(ev);
	    free(ev);
            (void) close(soc);
            return;
        }
        if (len == 0) {
            /* エンド・オブ・ファイル */
            (void) fprintf(stderr, "recv:EOF\n");
	    	(void) event_del(ev);
	    	//free(ev);
            (void) close(soc);
            return;
        }

		getnameinfo((struct sockaddr *)&info, info_len,
			addr_buf, sizeof(addr_buf),
			port_buf, sizeof(port_buf),
			NI_NUMERICHOST | NI_NUMERICSERV);
		fprintf(stderr, "recvfrom:%s:%s:len=%d\n",
			addr_buf, port_buf, (int)len);

        /* 文字列化・表示 */
        buf[len]='\0';
        if ((ptr = strpbrk(buf, "\r\n")) != NULL) {
            *ptr = '\0';
        }
        (void) fprintf(stderr, "[client]%s\n", buf);
		
		if(!strcmp(buf, "shutdown")){
			fprintf(stderr, "shutdown tcpserver\n");
			event_del(ev);
			//free(ev);
			close(soc);
			event_loopexit(NULL);
			return;
		}

        /* 応答文字列作成 */
        (void) mystrlcat(buf, ":OK\r\n", sizeof(buf));
        len = (ssize_t) strlen(buf);
        /* 応答 */
        if ((len = sendto(soc, buf, (size_t) len, 0, 
						(struct sockaddr *)&info, info_len)) == -1) {
            /* エラー */
            perror("sendto");
	    	(void) event_del(ev);
	    	//free(ev);
            (void) close(soc);
        }

    }
}


void sig_int_handler(int fd, short event, void *arg)
{
	fprintf(stdout, "\n");
	event_loopexit(NULL);
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

		fprintf(stderr, "[receiver] read '%s'\n", buf);

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
	int c, index;

	struct event ev;
	struct event sig;

	struct event io_ev;

	struct option options[] = {
		{ "host", required_argument, 0, 'h' },
		{ "port"    , required_argument, 0, 'p' },
		{ "multicast-address", required_argument, 0, 'm' },
		{ 0, 0, 0, 0 }
	};

	const char *host = NULL;
	const char *port = NULL;
	const char *multicast_address = NULL;

	int soc;

	int err;

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
#if 0
	if(multicast_address == NULL){
		fprintf(stderr, "no multicast-address option\n");
		ret++;
	}

#endif

	if(ret){
		exit(1);
	}

	
	event_init();
	signal_set(&sig, SIGINT, sig_int_handler, NULL);
	signal_add(&sig, NULL);

	soc = receiver_socket(host, port, multicast_address);
	if(soc == -1){
		fprintf(stderr, "receiver_socket failed\n");
		exit(1);
	}

	event_set(&ev, soc, EV_READ | EV_PERSIST, recv_handler, &ev);
	err = event_add(&ev, NULL);
	if(err != 0){
		perror("event_add");
		close(soc);
		exit(1);
	}

#if 1
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	event_set(&io_ev, 0 /* stdin */, EV_READ | EV_PERSIST,
			read_stdin, &io_ev);
	event_add(&io_ev, NULL);
	fprintf(stdout, "> ");
#endif

	event_dispatch();
	fprintf(stderr, "END\n");
	return 0;
}


