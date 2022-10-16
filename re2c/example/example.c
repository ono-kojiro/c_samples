#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>
#include <assert.h>

#include <unistd.h>
#include <getopt.h>

//#include "parser.h"
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

#if 0
	bufsize = Scanner_GetBufSize(s);

    for (i = 0; i < bufsize; ++i) {
        fwrite(content, 1, sizeof(content) - 1, f);
    }
    fclose(f);
    int count = 3 * bufsize; // number of quoted strings written to file
#endif

    // Initialize lexer state: all pointers are at the end of buffer.
    // This immediately triggers YYFILL, as the check `in.cur < in.lim` fails.

    for(i = optind; i < argc; i++){
        input = argv[i];
	    s = Scanner_Create();
	    Scanner_Init(s);

	    Scanner_Open(s, input);

        while(1){
	        ret = Scanner_Scan(s, &id);
            if(ret != 0){
                break;
            }
        }

	    Scanner_Delete(s);
    }
   
    // Cleanup: remove input file.
    //remove(fname);
    
    if(output){
        fclose(out);
    }

    if(ret == EOF){
        ret = 0;
    }

	return ret;
}
