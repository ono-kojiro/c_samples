#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>

#include "parser.h"
#include "scanner.h"

int main(int argc, char **argv){
    Scanner in;
	YYSTYPE yylval;

	/* Parser */
	void *parser = NULL;
	Token t0, t1;
	Token mToken;
	char buf[256];

	/* Userdata */
	USERDATA *userdata = NULL;

    int t;
    memset((char*) &in, 0, sizeof(in));
    in.fd = 0;

	parser = (void *)ParseAlloc(malloc);
	if(!parser){
		fprintf(stderr, "ParseAlloc failed\n");
		exit(1);
	}

	userdata = Userdata_Create();
	if(!userdata){
		fprintf(stderr, "Userdata_Create failed\n");
		exit(1);
	}

	t0.n = 0;
	t0.value = 0;

	ParseInit(parser);

    while((t = scan(&in, &yylval)) != EOF){
		fprintf(stderr, "DEBUG : %d\t%.*s\n", t, in.cur - in.tok, in.tok);
		fprintf(stderr, "DEBUG : %d\n", t);
		fprintf(stderr, "Next\n");
#if 1
		sprintf(buf, "%.*s", in.cur - in.tok, in.tok);
		t0.value = atoi(buf);
		Parse(parser, t, t0, userdata);
#endif
    }

	//Parse(parser, t, t0);
	ParseFree(parser, free);
	Userdata_Delete(userdata);
    close(in.fd);
}
