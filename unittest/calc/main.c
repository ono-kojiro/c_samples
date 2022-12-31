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
	Token token;
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
#ifndef NDEBUG
	MyParserTrace(stderr, "PARSER : ");
#endif

    while((token_id = scan(&in, &yylval)) != EOF){
#ifndef NDEBUG
		fprintf(stderr, "%s(%d) : ", __FILE__ , __LINE__ );
		fprintf(stderr, "token(%d), ", token_id);
		if(isprint(in.tok[0])){
			fprintf(stderr, "'%.*s'\n", in.cur - in.tok, in.tok);
		}
		else {
			fprintf(stderr, "'0x%X'\n", in.tok[0]);
		}
		
#endif
        token.z = in.tok;
        token.n = in.cur - in.tok;
        sprintf(buf, "%.*s", token.n, token.z);
		token.value = atoi(buf);
#ifndef NDEBUG
        fprintf(stderr, "[DEBUG] call MyParser(%d)\n", token.value);
#endif
		MyParser(parser, token_id, token, userdata);
    }

	MyParser(parser, 0, token, userdata);
#ifndef NDEBUG
    fprintf(stderr, "[DEBUG] loop finished\n");
#endif
    fprintf(stdout, "%d\n", userdata->result);
	MyParserFree(parser, free);
	Userdata_Delete(userdata);
    close(in.fd);
}
