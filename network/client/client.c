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
        buf[len] = '\0';
		fprintf(stderr, "DEBUG : '%s'\n", buf);

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
void recv_handler(int soc, short event, void *arg)
{
    char buf[512], *ptr;
    ssize_t len;
    /* event_set()の第５引数のデータをargで受け取れる */
    struct event *ev = (struct event*) arg;

    /* イベントのタイプが読み込み可能だった */
    if (event & EV_READ) {
        /* 受信 */
        if ((len = recv(soc, buf, sizeof(buf), 0)) == -1) {
            /* エラー */
            perror("recv");
			close(soc);
            return;
        }

        if (len == 0) {
            /* エンド・オブ・ファイル */
            (void) fprintf(stderr, "recv:EOF\n");
			close(soc);
            return;
        }
        /* 文字列化・表示 */
        buf[len]='\0';
        if ((ptr = strpbrk(buf, "\r\n")) != NULL) {
            *ptr = '\0';
        }
        (void) fprintf(stderr, "[server]%s\n", buf);
#if 0
        /* 応答文字列作成 */
        (void) mystrlcat(buf, ":OK\r\n", sizeof(buf));
        len = (ssize_t) strlen(buf);
        /* 応答 */
        if ((len = send(acc, buf, (size_t) len, 0)) == -1) {
            /* エラー */
            perror("send");
	    	(void) event_del(ev);
			free(ev);
            (void) close(acc);
        }
#endif
    }
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


