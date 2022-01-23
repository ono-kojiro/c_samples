#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>

#include <regex.h>

#include "scanner.h"

#include "reduce_path.h"

int test(char *str)
{
    regex_t re;

    int i;
    int status;
    int ret;
    char *token;
    int start, end;
    size_t size;
    int len;

    char pattern[] = "/([^/]+/\\.\\./|\\./)";

    regmatch_t matches[2];

    printf("INPUT : '%s'\n", str);
    ret = regcomp(&re, pattern, REG_EXTENDED);
    if(ret != 0){
        fprintf(stderr, "ERROR : regcomp failed\n");
        exit(1);
    }

    while(1){
        ret = regexec(&re, str, 2, matches, REG_NOTBOL | REG_NOTEOL);
        if(ret == REG_NOMATCH){
            break;
        }

        start = matches[1].rm_so;
        end   = matches[1].rm_eo;

        printf("rm_so is %d\n", start);
        printf("rm_eo is %d\n", end);
    
        token = strndup(str + start, end - start);
        printf("debug : '%s'\n", token);
        free(token);

        len = strlen(str);
        memmove(str + start, str + end, len - end);
        str[len - (end - start)] = '\0';
        printf("after memmove : '%s'\n", str);
    }

    regfree(&re);
}

int main(int argc, char **argv)
{
    int ret;
    SCANNER s;
    int count = 0;

    //const char buf_in[] = "/aaa/bbb/ccc";
    char buf_in[] = "/aaa/bbb/ccc/../ddd/eee/./fff/ggg";
    char *buf_out;
    size_t out_len;
    int token_len;
    int len;

    s.cursor = buf_in;
    s.limit  = buf_in + strlen(buf_in);
    
    buf_out = strdup(buf_in);
    memset(buf_out, 0, strlen(buf_out));

    while(1){
        if(s.cursor <= s.limit){
            printf("current input is '%s'\n", s.cursor);
        }
        ret = scan(&s);
        printf("scan end\n");
        if(!ret){
            break;
        }

        len = (int)(s.cursor - s.token);
        printf("token is '%.*s', ret is %d\n", len, s.token, ret);

        out_len = strlen(buf_out);
        token_len = (int)(s.cursor - s.token);
        sprintf(buf_out + out_len, "%.*s", token_len, s.token);
        count++;
        if(count >= 10){
            break;
        }
    }

    printf("buf_out is '%s'\n", buf_out);

    printf("INPUT  : '%s'\n", buf_in);
    reduce_path(buf_in);
    printf("OUTPUT : '%s'\n", buf_in);

    free(buf_out);
    return 0;
}

