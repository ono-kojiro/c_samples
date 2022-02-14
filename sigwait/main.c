#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include <signal.h>

#include <pthread.h>
#include <unistd.h>

struct USERDATA {
    int argc;
    char **argv;
    FILE *fp;
};

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

int main(int argc, char **argv)
{
    int ret = 0;
    int i;

    sigset_t ss;
    int signo;
    void *retval = (void *)(intptr_t)(-1);

    pthread_t pt;
    pthread_attr_t attr;

    struct USERDATA userdata;

    int signals[] = { SIGHUP, SIGINT, SIGUSR1, SIGUSR2 };
    
    int c;
    int index;
    struct option options[] = {
        { "help", no_argument, 0, 'h' },
        { "version", no_argument, 0, 'v' },
        { "output", required_argument, 0, 'o' },
        { 0, 0, 0, 0 }
    };

    const char *output = NULL;
    FILE *fp = NULL;

    ret = sigemptyset(&ss);
    if(ret){
        perror("sigemptyset");
        exit(1);
    }

    for(i = 0; i < sizeof(signals)/sizeof(signals[0]); i++){
        ret = sigaddset(&ss, signals[i]);
        if(ret){
            perror("sigaddset");
            exit(1);
        }
    }

    sigprocmask(SIG_BLOCK, &ss, NULL);

    while(1){
        c = getopt_long(argc, argv, "hvo:", options, &index);
        if(c == -1){
            break;
        }

        switch(c){
            case 'h' :
                break;
            case 'v' :
                break;
            case 'o' :
                output = optarg;
                break;
            default :
                break;
        }
    }

    if(!output){
        printf("ERROR : no output option\n");
        ret++;
    }

    if(ret){
        exit(ret);
    }

    fp = fopen(output, "wt");
    if(!fp){
        perror(output);
        exit(1);
    }

    userdata.argc = argc;
    userdata.argv = argv;
    userdata.fp   = fp;
    
    fprintf(fp, "start thread\n");
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&pt, &attr, main_thread, &userdata);
    

    while(1){
        if(sigwait(&ss, &signo) == 0){
            switch(signo){
                case SIGHUP:
                    fprintf(stderr, "catched SIGHUP\n");
                    pthread_cancel(pt);
                    break;
                case SIGINT:
                    fprintf(stderr, "catched SIGINT\n");
                    pthread_cancel(pt);
                    break;
                case SIGUSR1:
                    fprintf(stderr, "catched SIGUSR1\n");
                    break;
                case SIGUSR2:
                    fprintf(stderr, "catched SIGUSR2\n");
                    break;
                default :
                    fprintf(stderr, "catched unknown signal\n");
                    break;
            }
            break;
        }
        else{
            printf("sigwait failed\n");
        }
    }

    pthread_join(pt, &retval);
    ret = (int)(intptr_t)retval;
    printf("thread exited with %d\n", ret);

    fprintf(fp, "thread finished\n");
    if(fp){
        fclose(fp);
    }
    if(ret){
        printf("INFO : remove %s\n", output);
        remove(output);
    }
    printf("end of main\n");
    return ret;
}


