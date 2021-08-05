#include <stdlib.h>
#include <memory.h>

#include "scanner.h"
#include "userdata.h"

USERDATA *create_userdata()
{
	USERDATA *self = (USERDATA *)malloc(1 * sizeof(USERDATA));
	memset(self, 0, 1 * sizeof(USERDATA));

	self->buf_size = sizeof(self->buf);
	return self;
}

int destroy_userdata(USERDATA *self)
{
	if(self){
		free(self);
	}

	return 0;
}


