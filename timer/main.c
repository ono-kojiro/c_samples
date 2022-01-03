#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include <pthread.h>
#include <event.h>
#include <event2/thread.h>

#include <getopt.h>

#include <unistd.h>
#include <fcntl.h>

typedef struct _USERDATA {
	pthread_t thread;
	struct event_base *evbase;
	int debug;
} USERDATA;

void sigint_handler(int fd, short event, void *arg)
{
	USERDATA *userdata;
	struct event_base *evbase;
	pthread_t thread;
	int ret;

	userdata = (USERDATA *)arg;

	if(userdata->debug){	
		fprintf(stderr, "sigint_handler\n");
		fprintf(stderr, "call pthread_cancell\n");
	}

	ret = pthread_cancel(userdata->thread);
	if(ret != 0){
		fprintf(stderr, "pthread_cancel failed\n");
	}

	if(userdata->debug){
		fprintf(stderr, "call event_base_loopback\n");
	}

	event_base_loopbreak(userdata->evbase);
}

void timer_handler(int fd, short event, void *arg)
{
	fprintf(stderr, "this is timer handler\n");
}

void *thread_func(void *arg)
{
	USERDATA *userdata;
	struct event_base *evbase;

	sigset_t set;

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	

	userdata = (USERDATA *)arg;

	if(userdata->debug){
		fprintf(stderr, "This is thread_func.\n");
		fprintf(stderr, "%s : sleep(5)\n", __FUNCTION__);
	}

	sleep(5);

	if(userdata->debug){
		fprintf(stderr, "%s : call event_base_loopback\n",
			__FUNCTION__);
	}

	event_base_loopbreak(userdata->evbase);
#if 1
	fprintf(stderr, "pthread_exit(0)\n");
	pthread_exit(0);
#endif
}

int main(int argc, char **argv)
{
	int ret = 0;
	int c, index;

	struct option options[] = {
		{ "help",     no_argument, 0, 'h' },
		{ 0, 0, 0, 0 }
	};

	/* for input file */
	const char *input;
	FILE *fp_in = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	struct event_base *evbase;
	struct event *ev_int;
	struct event *ev_timer;

	struct timeval tv;

	pthread_t thread;
	void *res;

	struct thread_info *tinfo;
	USERDATA userdata;

	int debug = 0;

	while(1){
		c = getopt_long(argc, argv,
			"hd",
			options, &index);
		if(c == -1){
			break;
		}

		switch(c){
			case 'h' :
				break;
			case 'd' :
				debug = 1;
			default :
				break;
		}
	}

#if 0
	if(output == NULL){
		fprintf(stderr, "no output option\n");
		ret++;
	}
#endif
	
	if(ret){
		exit(1);
	}

	userdata.debug = debug;

	evthread_use_pthreads();
	evbase = event_base_new();
	
	userdata.evbase = evbase;
	
	ret = pthread_create(&thread, NULL,
		thread_func, &userdata);
	if(debug){
		fprintf(stderr, "thread is %ld\n", thread);
	}

	userdata.thread = thread;
	
	
	ev_int   = event_new(evbase, SIGINT,
		EV_SIGNAL | EV_PERSIST, 
		sigint_handler, &userdata);
	event_add(ev_int, NULL);

	ev_timer = event_new(evbase, -1, EV_PERSIST, timer_handler, &userdata);
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	evtimer_add(ev_timer, &tv);
	
	event_base_dispatch(evbase);
	if(debug){
		fprintf(stderr, "event_base_dispatch finished.\n");
	}

	ret = pthread_cancel(thread);
	if(ret == 0){
		if(debug){
			fprintf(stderr, "pthread_cancel success\n");
		}
	}
	else{
		if(debug){
			fprintf(stderr, "pthread_cancel failed\n");
		}
	}

	/* join with thread */
	if(ret){
		pthread_join(thread, &res);
		if(debug){
			fprintf(stderr, "thread returned %s\n",
				(char *)res);
		}
		if(res){
			free(res);
		}
	}

	event_free(ev_int);
	event_base_free(evbase);
	return 0;
}


