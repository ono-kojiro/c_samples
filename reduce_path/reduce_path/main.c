#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>

#include "scanner.h"

int main(int argc, char **argv)
{
    int ret;
    SCANNER s;
    int count = 0;

    const char buf_in[] = "/aaa/bbb/ccc";
    s.cursor = buf_in;
    s.limit  = buf_in + strlen(buf_in);
    
    while(1){
        if(s.cursor <= s.limit){
            printf("current input is '%s'\n", s.cursor);
        }
        ret = scan(&s);
        printf("scan end\n");
        if(!ret){
            break;
        }

        printf("token is '%.*s', ret is %d\n", s.cursor - s.token, s.token, ret);

        count++;
        if(count >= 10){
            break;
        }
    }

    return 0;
}

