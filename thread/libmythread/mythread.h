#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <stdio.h>

void *main_thread(void *arg);

struct USERDATA {
    int argc;
    char **argv;
    FILE *fp;
};

#endif /* #ifndef MYTHREAD_H */

