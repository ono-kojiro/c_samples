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

void sig_int_handler(int fd, short event, void *arg)
{
	event_loopexit(NULL);
}

void timer_handler(int fd, short event, void *arg)
{
	event_loopexit(NULL);
}


int main(int argc, char **argv)
{
	int ret = 0;
	int c, index;

	struct option options[] = {
		{ "output",     required_argument, 0, 'o' },
		{ "binary",     required_argument, 0, 'b' },
		{ 0, 0, 0, 0 }
	};

	/* const char *host = NULL; */
	const char *output = NULL;
	FILE *fp_out = NULL;
	
	/* for input file */
	const char *input;
	FILE *fp_in = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	ssize_t nwrite;

	int i;
	char ch;
	char buf3[3];

	struct event_base *evbase;
	struct event *ev_int;
	struct event *ev_timer;

	const char *binary = NULL;
	unsigned char bin = 0;

	while(1){
		c = getopt_long(argc, argv,
			"o:b:",
			options, &index);
		if(c == -1){
			break;
		}

		switch(c){
			case 'o' :
				output = optarg;
				break;
			case 'b' :
				binary = optarg;
				break;
			default :
				break;
		}
	}

	if(output == NULL){
		fprintf(stderr, "no output option\n");
		ret++;
	}
	
	if(ret){
		exit(1);
	}
	
	if(binary){
		sscanf(binary, "%hhx", &bin);
		printf("INFO : binary is 0x%x\n", bin);
	}
	


	//evthread_use_pthreads();

	evbase = event_base_new();
	
	ev_int = event_new(evbase, SIGINT, EV_PERSIST, sig_int_handler, NULL);
	event_base_dispatch(evbase);
	
	fp_out = fopen(output, "wb");
	if(!fp_out){
		fprintf(stderr, "can not open %s\n", output);
		perror(argv[0]);
		exit(1);
	}

#if 0
	buf3[0] = 'a';
	buf3[1] = 'b';
	buf3[2] = 'c';
	fwrite(buf3, sizeof(char), 3, fp_out);
	buf3[0] = 0xFF;
	buf3[1] = 0xFD;
	fwrite(buf3, sizeof(char), 2, fp_out);
#endif

	for(index = optind; index < argc; index++){
		input = argv[index];
		fprintf(stderr, "open %s\n", input);
		fp_in = fopen(input, "rt");
		if(!fp_in){
			perror(argv[0]);
			ret = 1;
			break;
		}
		while(1){
			nread = getline(&line, &len, fp_in);
			if(nread == -1){
				break;
			}
			
			printf("LINE : %s", line);
			for(i = 0; i < nread; i++){
				if(bin != 0){
					buf3[0] = 0xFF;
					buf3[1] = bin;
					buf3[2] = line[i];
					nwrite = 3;
				}
				else {
					buf3[0] = line[i];
					nwrite = 1;
				}

				fwrite(buf3, sizeof(char), nwrite, fp_out);
			}
			/* fwrite(line, sizeof(char), nread, fp_out); */
		}
		fclose(fp_in);
	}

	if(bin == 0){
		buf3[0] = 0xFF;
		buf3[1] = 0xFD;
		fwrite(buf3, sizeof(char), 2, fp_out);
	}

	if(line){
		free(line);
	}
	fclose(fp_out);

	event_free(ev_int);
	event_base_free(evbase);
	return ret;
}


