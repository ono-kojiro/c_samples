#include <stdio.h>

#include "mystaticlib.h"

int mystaticlib(void)
{
    unsigned long long c;
    unsigned long long l, t;
    unsigned long long n = 0;

    unsigned int max_prime = 3000000;
    
    printf("this is mystaticlib.\n");

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

