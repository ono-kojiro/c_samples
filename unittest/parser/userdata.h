#ifndef USERDATA_H
#define USERDATA_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _USERDATA {
  int state;
  int result;
  int accept;
  int failure;
  int error;
} USERDATA;

USERDATA *Userdata_Create();
int Userdata_Delete(USERDATA *self);
int Userdata_Init(USERDATA *self);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef USERDATA_H */


