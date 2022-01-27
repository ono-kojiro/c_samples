#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>

#include "shortpath.h"

int main(int argc, char **argv)
{
    int ret;

    struct option options[] = {
        { "help", no_argument, 0, 0 },
        { "version", no_argument, 0, 0 },
        { "output",  required_argument, 0, 0 },
        { 0, 0, 0, 0 }
    };

    const char *output = NULL;
    FILE *fp = NULL;

    int c, index;
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
        fp = fopen(output, "wt");
    }
    else {
        fp = stdout;
    }

    while(optind < argc){
        //fprintf(fp, "before '%s'\n", argv[optind]);
        shortpath(argv[optind]);
        fprintf(fp, "%s\n", argv[optind]);
        optind++;
    }
    
    if(output){
        fclose(fp);
    }

    return 0;
}

