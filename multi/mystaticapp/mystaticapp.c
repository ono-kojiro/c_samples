#include <stdio.h>
#include <math.h>

#include "mystaticlib.h"

int main(int argc, char **argv)
{
    unsigned long long c;
    unsigned long long l, t;
    unsigned long long n = 0;

    unsigned int max_prime = 2000000;
    printf("This is mystaticapp.\n");

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

	mystaticlib();
	return 0;
}

