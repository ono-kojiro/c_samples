#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>
#include <assert.h>

#include <unistd.h>
#include <getopt.h>

#include <sqlite3.h>

#include "parser.h"
#include "scanner.h"

int main(int argc, char **argv)
{
    int c, index;
    int ret = 0;

    struct option options[] = {
        { "help", no_argument, 0, 'h' },
        { "version", no_argument, 0, 'v' },
        { "output", required_argument, 0, 'o' },
        { 0, 0, 0, 0 }
    };

    const char *input  = NULL;
    const char *output = NULL;
    FILE *in = NULL;
    FILE *out = NULL;

    const char *fname = "input";
    const char content[] = "'qu\0tes' 'are' 'fine: \\'' ";

	int bufsize;

    // Prepare input file: a few times the size of the buffer, containing
    // strings with zeroes and escaped quotes.
    //FILE *f = fopen(fname, "w");
	int i;

	SCANNER *s;
    int id;

	void *parser = NULL;
	Token token;

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

    if(output){
        out = fopen(output, "wt");
    }
    else {
        out = stdout;
    }

    for(i = optind; i < argc; i++){
        input = argv[i];
	    s = Scanner_Create();
	    Scanner_Init(s);

		parser = (void *)ParseAlloc(malloc);
		if(!parser){
			fprintf(stderr, "ParseAlloc failed\n");
			exit(1);
		}
		ParseTrace(stdout, "DEBUG :");
		ParseInit(parser);

	    Scanner_Open(s, input);

        while(1){
	        ret = Scanner_Scan(s, &id);
            if(ret != 0){
                break;
            }

			Parse(parser, ret, token);
        }

	    Scanner_Delete(s);
		ParseFree(parser, free);
    }
   
    if(output){
        fclose(out);
    }

    if(ret == EOF){
        ret = 0;
    }

	return ret;
}
