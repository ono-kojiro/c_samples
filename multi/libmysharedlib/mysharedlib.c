#include <stdio.h>
#include <math.h>

#include "mysharedlib.h"

int mysharedlib(void)
{
    unsigned long long c;
    unsigned long long l, t;
    unsigned long long n = 0;

    unsigned int max_prime = 5000000;
    
    printf("this is mysharedlib.\n");

    for(c=3; c < max_prime; c++)  
    {
        t = sqrt(c);
        for(l = 2; l <= t; l++){
            if (c % l == 0){
                break;
            }
        }
        if (l > t ){
            n++;
        }
    }
    return 0;
}

