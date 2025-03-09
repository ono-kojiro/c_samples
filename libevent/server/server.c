#include <stdio.h>
#include <stdlib.h>

/* for MAX_PATH */
#include <limits.h>

/* for strerror() */
#include <string.h>

/* for errno */
#include <errno.h>

#include <syslog.h>

/* for signal() */
#include <signal.h>

/* for dup2() */
#include <unistd.h>

/* for O_RDWR */
#include <fcntl.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXFD 64

#include <getopt.h>

#include <event2/event.h>
#include <event2/bufferevent.h>

struct userdata {
    char ip_str[INET6_ADDRSTRLEN];
    int  port;
};

void get_addr_and_port(struct sockaddr *sa, char *ip_str, int *port)
{
    //char ip_str[INET6_ADDRSTRLEN];
    if(sa->sa_family == AF_INET){
        // IPv4
        struct sockaddr_in *sa_in = (struct sockaddr_in *)sa;
        inet_ntop(AF_INET, &(sa_in->sin_addr), ip_str, INET_ADDRSTRLEN);
        *port = ntohs(sa_in->sin_port);
    }
    else if(sa->sa_family == AF_INET6){
        // IPv6
        struct sockaddr_in6 *sa_in6 = (struct sockaddr_in6 *)sa;
        inet_ntop(AF_INET6, &(sa_in6->sin6_addr), ip_str, INET6_ADDRSTRLEN);
        *port = ntohs(sa_in6->sin6_port);
    }
    else {
        strcpy(ip_str, "Unknown AF");
        *port = -1;
    }
}

void read_cb(struct bufferevent *bev, void *ctx)
{
    char buffer[256];
    struct userdata *data = (struct userdata *)ctx;
    int n;
    while(1){
        n = bufferevent_read(bev, buffer, sizeof(buffer));
        if(n <= 0){
            break;
        }
        printf("Received from %s:%d: %s", data->ip_str, data->port, buffer);
        bufferevent_write(bev, buffer, n); // echo back
    }
}

void event_cb(struct bufferevent *bev, short events, void *ctx)
{
    struct userdata *data = (struct userdata *)ctx;
    int finished = 0;

    if(events & (BEV_EVENT_EOF)){
        perror("BEV_EVENT_EOF");
        finished = 1;
    }
    if(events & BEV_EVENT_ERROR){
        perror("BEV_EVENT_ERROR");
        finished = 1;
    }

    if(finished){
        free(data);
        bufferevent_free(bev);
    }
}

void accept_cb(evutil_socket_t soc, short event, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
    struct sockaddr_in sin;
    struct bufferevent *bev;
    int fd;
    
    char ip_str[INET6_ADDRSTRLEN];
    int port = 0;

    struct userdata *data = NULL;
    data = (struct userdata *)malloc(1 * sizeof(struct userdata));

    socklen_t slen = sizeof(sin);
    fd = accept(soc, (struct sockaddr*)&sin, &slen);
    if(fd < 0){
        perror("accept");
        return;
    }

    get_addr_and_port((struct sockaddr *)&sin, ip_str, &port);
    fprintf(stderr, "DEBUG: accept from %s:%d\n", ip_str, port);
    strcpy(data->ip_str, ip_str);
    data->port = port;

    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_cb, NULL, event_cb, (void *)data);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void signal_handler(int sig)
{
    switch(sig){
        case SIGHUP:
		    syslog(LOG_INFO, "Hangup Signal Catched");
            break;
        case SIGTERM:
	    	syslog(LOG_INFO, "Terminate Signal Catched");
	    	closelog();
            exit(0);
            break;
        default :
            break;
    }
}

int daemonize(int flag)
{
    int i;
    int ret;
    int fd = 0;

    pid_t pid = 0;
    pid = fork();
    if(pid == -1){
        /* failure */
        return -1;
    }
    else if(pid != 0){
        /* parent process */
        /* pid is PID of the child process */
        _exit(0);
    }

    /* child process */
  
    setsid();

    signal(SIGCHLD, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);

    signal(SIGHUP,  signal_handler);
    signal(SIGTERM, signal_handler);

    pid = fork();
    if(pid == 0){
        /* child process */
        _exit(0);
    }

    /* parent process */

    if(flag == 0){
        ret = chdir("/");
        if(!ret){
            perror("chdir");
            exit(ret);
        }
    }

    for(i = 0; i < MAXFD; i++){
        close(i);
    }

    fd = open("/dev/null", O_RDWR, 0);
    if(fd != -1){
        dup2(fd, 0);
        dup2(fd, 1);
        dup2(fd, 2);
        if(fd < 2){
            close(fd);
        }
    }

    return 0;
}

int start_server(const char *port)
{
	int soc;
	int err;
    struct event_base *base = NULL;

    struct addrinfo *info = NULL;

	const char *host = "localhost";
	/* const char *port = "9999"; */

    base = event_base_new();
    if(!base){
	    syslog(LOG_ERR, "event_base_new failed");
        exit(1);
    }

    {
        /*
            in:  host, port
            out: info
        */
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        err = getaddrinfo(host, port, &hints, &info);
        if(err != 0){
            fprintf(stderr, "getaddrinfo():%s\n", gai_strerror(err));
            return -1;
        }
    }

    {
        char host_buf[NI_MAXHOST];
        char serv_buf[NI_MAXSERV];
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

        fprintf(stderr, "addr=%s, port=%s\n", host_buf, serv_buf);
    }

    soc = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if(soc < 0){
	    syslog(LOG_INFO, "socket failed");
        freeaddrinfo(info);
        exit(1);
    }

    {
        int opt = 1;
        socklen_t opt_len;

        opt_len = sizeof(opt);
        err = setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &opt, opt_len);
        if(err == -1){
            perror("setsockopt");
            close(soc);
            freeaddrinfo(info);
            return -1;
        }
    }

    err = bind(soc, info->ai_addr, info->ai_addrlen);
    if(err < 0){
        perror("bind");
        close(soc);
        freeaddrinfo(info);
        return -1;
    }

    {
        err = listen(soc, SOMAXCONN);
        if(err < 0){
            perror("listen");
            return -1;
        }
    }

    {
        struct event *ev;
        ev = event_new(
            base, soc, EV_READ | EV_PERSIST, accept_cb, (void *)base);
        err = event_add(ev, NULL);
	    if(err != 0){
	        syslog(LOG_INFO, "event_add failed");
		    close(soc);
		    exit(1);
	    }
	}

	event_base_dispatch(base);
	return 0;
}

int main(int argc, char **argv)
{
    int ret = 0;
    int c;
    int index;

    struct option options[] = {
        { "help",       no_argument, 0, 'h' },
        { "foreground", no_argument, 0, 'F' },
        { "port", required_argument, 0, 'p' },
        { 0, 0, 0, 0 }
    };
    const char *port = NULL;
    int show_help = 0;
    int is_foreground = 0;

    char buf[PATH_MAX];
    char *str;

    while(1){
        c = getopt_long(argc, argv, "hp:F", options, &index);
        if(c == -1){
            break;
        }

        switch(c){
            case 'h' :
                show_help = 1;
                break;
            case 'p' :
                port = optarg;
                break;
            case 'F' :
                is_foreground = 1;
                break;
        }
    }

    if(show_help){
        printf("Usage: %s <options>\n", argv[0]);
        printf("  options:\n");
        printf("\n");
        printf("  -h, --help\n");
        printf("  -p, --port\n");
        printf("  -F, --foreground\n");
        exit(1);
    }

    if(!port){
        fprintf(stderr, "ERROR: no port option\n");
        ret++;
    }

    if(ret){
        exit(ret);
    }


    if(!is_foreground){
        openlog(argv[0], LOG_CONS | LOG_PID, LOG_USER);
        syslog(LOG_INFO, "call daemonize()");
        daemonize(1);
    }
    else {
        openlog(NULL, LOG_PERROR, LOG_USER);
        syslog(LOG_INFO, "call daemonize()");
    }
    str = getcwd(buf, sizeof(buf));

    if(str == NULL){
        str = strerror(errno);
        syslog(LOG_USER | LOG_NOTICE, "daemon:%s\n", str);
    }
    else {
        syslog(LOG_USER | LOG_NOTICE, "daemon:cwd=%s\n", buf);
    }

	/*
    while(1){
        sleep(1);
    }
	*/
	start_server(port);

    closelog();

    return 0;
}

