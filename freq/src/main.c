#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include <signal.h>

#include <regex.h>

static volatile int terminate = 0;

static void signal_handler(int sig)
{
    if(sig == SIGTERM){
        exit(1);
    }
    else if(sig == SIGINT){
        if(terminate){
            exit(2);
        }

        terminate = 1;
    }
}

int main(int argc, char **argv)
{
    int ret = 0;
    int i;

    struct sigaction sig_action;
    
    int c;
    int index;
    struct option options[] = {
        { "help", no_argument, 0, 'h' },
        { "version", no_argument, 0, 'v' },
        { "output", required_argument, 0, 'o' },
        { 0, 0, 0, 0 }
    };

    const char *output = NULL;
    FILE *fp = NULL;

    regex_t *regexes = NULL;
    regex_t *regex = NULL;
    int nregex = 0;
    regmatch_t *regmatches = NULL;
    int nregmatch = 10;
    
    char *input = NULL;
    ssize_t nread;
    size_t len = 0;

    char *line = NULL;
    FILE *in   = NULL;


    while(1){
        c = getopt_long(argc, argv,
            "hvo:", options, &index);
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

    if(ret){
        exit(ret);
    }

    if(output){
        fp = fopen(output, "wt");
        if(!fp){
            perror(output);
            exit(1);
        }
    }
    else{
        fp = stdout;
    }


    memset(&sig_action, 0, sizeof(sig_action));
    sig_action.sa_handler = signal_handler;
    sigaction(SIGINT, &sig_action, NULL);

    nregex = argc - optind;
    regexes = (regex_t *)malloc(nregex * sizeof(regex_t));
    memset(regexes, 0, nregex * sizeof(regex_t));

    regmatches = (regmatch_t *)malloc(nregmatch * sizeof(regmatch_t));
    memset(regmatches, 0, nregmatch * sizeof(regmatch_t));

    for(i = 0; i < nregex; i++){
        const char *pattern= NULL;
        FILE *in;

        pattern = argv[optind + i];
        ret = regcomp(regexes + i, pattern, REG_NEWLINE);
        if(ret != 0){
            fprintf(stderr, "ERROR : regcomp failed\n");
            exit(1);
        }
    }

    while(1){
        int nline = 0;
        int b_first = 1;

        nread = getline(&input, &len, stdin);
        if(nread == -1){
            break;
        }

        if(input[nread - 1] == '\n'){
            input[nread - 1] = '\0';
        }

#if 0
        for(i = 0; i < nread; i++){
            fprintf(stderr, "DEBUG : input[%d] = 0x%02x\n", i, input[i]);
        }
        fprintf(stderr, "\n");
#endif

        in = fopen(input, "rt");
        if(!in){
            fprintf(stderr, "nread is %ld\n", nread);
            fprintf(stderr, "WARN: can not open '%s'\n", input);
            continue;
        }

        while(1){
            nread = getline(&line, &len, in);
            if(nread == -1){
                break;
            }
            nline++;
        
            if(line[nread - 1] == '\n'){
                line[nread - 1] = '\0';
            }
            //fprintf(stderr, "read %ld byte data\n", nread);
            //fprintf(stderr, "LINE: '%s'\n", line);

            for(i = 0; i < nregex; i++){
                regex = regexes + i;

                ret = regexec(regex, line, nregmatch, regmatches, 0);
                if(ret == 0){
                    if(b_first){
                        fprintf(stderr, "%s\n", input);
                    }
                    b_first = 0;
                    fprintf(stderr, "%d: %s\n", nline, line);
                }
            }
        }

        fclose(in);
    }

    if(regexes){
        free(regexes);
    }

    if(regmatches){
        free(regmatches);
    }
         
    if(input){
        free(input);
    }

    if(output){
        fclose(fp);
        fp = NULL;
    }

    return ret;
}


