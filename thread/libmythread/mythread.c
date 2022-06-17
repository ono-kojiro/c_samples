#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include <signal.h>

#include <pthread.h>
#include <unistd.h>

#include "mythread.h"

void *main_thread(void *arg)
{
    int ret;
    int i;

    int argc;
    char **argv;
    FILE *fp;

    struct USERDATA *userdata = (struct USERDATA *)arg;

    argc = userdata->argc;
    argv = userdata->argv;
    fp   = userdata->fp;

    printf("argc is %d\n", argc);
    printf("argv[0] is %s\n", argv[0]);

    for(i = 0; i < 3; i++){
        printf("sleep 1sec\n");
        sleep(1);
    }
    printf("end of thread\n");

    kill(getpid(), SIGUSR1);
    pthread_exit(0);
}

