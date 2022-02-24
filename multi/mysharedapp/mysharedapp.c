#include <stdio.h>
#include <math.h>

#include "mysharedlib.h"

int main(int argc, char **argv)
{
    unsigned long long c;
    unsigned long long l, t;
    unsigned long long n = 0;

    unsigned int max_prime = 4000000;
    
	printf("This is mysharedapp.\n");

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

	mysharedlib();
	return 0;
}

