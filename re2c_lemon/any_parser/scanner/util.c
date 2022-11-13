#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "util.h"

int is_digits(const unsigned char *start, const unsigned char *end,
    int base, unsigned long *val)
{
    int ret = 0;
    unsigned long sum = 0;

    int d;

    switch(base){
        case 8 :
        case 10 :
        case 16 :
            break;
        default :
            fprintf(stderr, "ERROR : invalid base number, %d\n", base);
            break;
    }

    /*
        check string like
        - '\123'
        - '\x34567'
    */

    while(start < end){
        d = (*start) - '0';
        if(sum > (ULONG_MAX - d) / base){
            ret = 1;
        }
        sum = sum * base + d;

        start++;
    }

    if(val != NULL){
        *val = sum;
    }

    return ret;
}

