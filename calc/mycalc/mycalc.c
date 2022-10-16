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
	Token token, t1;
	Token mToken;
	char buf[256];

	/* Userdata */
	USERDATA *userdata = NULL;

    int token_id;
    memset((char*) &in, 0, sizeof(in));
    in.fd = 0;

	parser = (void *)MyParserAlloc(malloc);
	if(!parser){
		fprintf(stderr, "MyParserAlloc failed\n");
		exit(1);
	}

	userdata = Userdata_Create();
	if(!userdata){
		fprintf(stderr, "Userdata_Create failed\n");
		exit(1);
	}

	token.n = 0;
	token.value = 0;

	MyParserInit(parser);

    while((token_id = scan(&in, &yylval)) != EOF){
		fprintf(stderr, "DEBUG : %d\t%.*s\n", token_id, in.cur - in.tok, in.tok);
		fprintf(stderr, "DEBUG : %d\n", token_id);
		fprintf(stderr, "Next\n");
#if 1
		sprintf(buf, "%.*s", in.cur - in.tok, in.tok);
		token.value = atoi(buf);
		MyParser(parser, token_id, token, userdata);
#endif
    }

	//Parse(parser, token_id, token);
	MyParserFree(parser, free);
	Userdata_Delete(userdata);
    close(in.fd);
}
