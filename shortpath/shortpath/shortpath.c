#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>

#include <regex.h>

int shortpath(char *path)
{

    int ret;
    
    int start, end;
    int len;
    regex_t re;

    /*
        remove '/aaa/../' and '/./' from path
    */
    char pattern[] = "/([^/]+/\\.\\./|\\./)";

    regmatch_t matches[2];

#ifdef DEBUG
    printf("INPUT : '%s'\n", path);
#endif

    ret = regcomp(&re, pattern, REG_EXTENDED);
    if(ret != 0){
        fprintf(stderr, "ERROR : regcomp failed\n");
        exit(1);
    }

    while(1){
        ret = regexec(&re, path, 2, matches, REG_NOTBOL | REG_NOTEOL);
        if(ret == REG_NOMATCH){
            break;
        }

        start = matches[1].rm_so;
        end   = matches[1].rm_eo;

#ifdef DEBUG
        {
            char *token;
            printf("rm_so is %d\n", start);
            printf("rm_eo is %d\n", end);

            token = strndup(path + start, end - start);
            printf("debug : '%s'\n", token);
            free(token);
        }
#endif

        len = strlen(path);
        memmove(path + start, path + end, len - end);
        path[len - (end - start)] = '\0';
#ifdef DEBUG
        printf("after memmove : '%s'\n", path);
#endif
    }

    regfree(&re);
}

