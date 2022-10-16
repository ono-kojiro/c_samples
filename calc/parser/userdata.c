#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "userdata.h"

USERDATA *Userdata_Create()
{
	USERDATA *self = (USERDATA *)malloc(1 * sizeof(USERDATA));
	if(self){
		memset(self, 0, 1 * sizeof(USERDATA));
	}
	return self;
}

int Userdata_Delete(USERDATA *self)
{
	if(self){
		free(self);
	}
	return 0;
}

int Userdata_Init(USERDATA *self)
{
	return 0;
}


