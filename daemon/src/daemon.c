#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <syslog.h>

#define RUNNING_DIR "/tmp"
#define LOCK_FILE "daemond.lock"
#define LOG_FILE "daemond.log"

#define USE_SYSLOG 1

/*
 *       daemon.c
 *
 *       Copyright 2010 Vasudev Kamath <kamathvasudev@gmail.com>
 *     
 *       This program is free software; you can redistribute it and/or modify
 *       it under the terms of the GNU Lesser General Public License as published by
 *       the Free Software Foundation; either version 3 of the License, or
 *       (at your option) any later version.
 *     
 *       This program is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *       GNU General Public License for more details.
 *      
 *       You should have received a copy of the GNU General Public License
 *       along with this program; if not, write to the Free Software
 *       Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *       MA 02110-1301, USA.
 */

void log_message(char *filename,char *message){
    FILE *logfile;
    logfile = fopen(filename,"a");
    if(!logfile)
        return;
    fprintf(logfile,"%s",message);
    fclose(logfile);
}

void signal_handler(int sig){
    switch(sig){
    case SIGHUP:
#if USE_SYSLOG
		syslog(LOG_INFO, "Hangup Signal Catched");
#else
        log_message(LOG_FILE,"Hangup Signal Catched");
#endif
        break;
    case SIGTERM:
#if USE_SYSLOG
		syslog(LOG_INFO, "Terminate Signal Catched");
		closelog();
#else
        log_message(LOG_FILE,"Terminate Signal Catched");
        closelog();
#endif
        exit(0);
        break;
    }
}

void daemonize(){
    int i,lfp;
    char str[10];
    int ret;

    if(getppid() == 1)
        return;
    i = fork();

    if(i < 0)
        exit(1);
    if(i > 0)
        exit(0);
    setsid();

    for(i = getdtablesize(); i >= 0; --i)
        close(i);

    i = open("/dev/null",O_RDWR);
    ret = dup(i);
    ret = dup(i);
    umask(027);

    ret = chdir(RUNNING_DIR);

    lfp = open(LOCK_FILE,O_RDWR|O_CREAT,0640);
    if(lfp < 0)
        exit(1);
    if(lockf(lfp,F_TLOCK,0) < 0)
        exit(1);

    sprintf(str,"%d\n",getpid());
    ret = write(lfp,str,strlen(str));

    signal(SIGCHLD,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);

    signal(SIGHUP,signal_handler);
    signal(SIGTERM,signal_handler);
}

int main(int argc,char **argv)
{
	openlog(argv[0], LOG_CONS | LOG_PID, LOG_USER);

	syslog(LOG_INFO, "call daemonize()");

    daemonize();
    while(1)
        sleep(1);

	closelog();
}

