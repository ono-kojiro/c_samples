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

#define MAXFD 64

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

int main(int argc, char **argv)
{
    char buf[PATH_MAX];
    char *str;

    openlog(argv[0], LOG_CONS | LOG_PID, LOG_USER);
    syslog(LOG_INFO, "call daemonize()");

    daemonize(1);
    str = getcwd(buf, sizeof(buf));

    if(str == NULL){
        str = strerror(errno);
        syslog(LOG_USER | LOG_NOTICE, "daemon:%s\n", str);
    }
    else {
        syslog(LOG_USER | LOG_NOTICE, "daemon:cwd=%s\n", buf);
    }

    while(1){
        sleep(1);
    }

    closelog();

    return 0;
}

