#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

STR *create_str(const char *str, int len)
{
  STR *self = (STR *)malloc(1 * sizeof(STR));
  if(!self){
    return NULL;
  }

  memset(self, 0, 1 * sizeof(STR));

  if(!str){
    self->s = strndup(str, len);
  }

  return self;
}

void delete_str(STR *self)
{
  if(self){
    if(self->s){
      free(self->s);
    }

    free(self);
  }
}

int set_str(STR *self, const char *str)
{
  int ret = 0;

  if(self){
    if(!self->s){
        self->s = strdup(str);
    }
    else {
      if(strlen(self->s) <= strlen(str)){
        free(self->s);
        self->s = strdup(str);
      }
      else{
        strcpy(self->s, str);
      }
    }
  }
  else{
    return 1;
  }

  return ret;
}


