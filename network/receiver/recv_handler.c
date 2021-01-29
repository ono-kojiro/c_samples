#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>

#include <event.h>

#include "recv_handler.h"

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

