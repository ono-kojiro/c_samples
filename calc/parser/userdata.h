#ifndef USERDATA_H
#define USERDATA_H

typedef struct _USERDATA {
  int state;
} USERDATA;

USERDATA *Userdata_Create();
int Userdata_Delete(USERDATA *self);
int Userdata_Init(USERDATA *self);

#endif /* #ifndef USERDATA_H */


