#ifndef USERDATA_H
#define USERDATA_H

#include <sqlite3.h>

typedef struct _USERDATA {
  int state;
  int count;
  sqlite3 *db;
} USERDATA;

USERDATA *Userdata_Create();
int Userdata_Delete(USERDATA *self);
int Userdata_Init(USERDATA *self);

int Userdata_OpenDatabase(USERDATA *self, const char *filepath);
int Userdata_CloseDatabase(USERDATA *self);
int Userdata_CreateTable(USERDATA *self);
int Userdata_DropTable(USERDATA *self);
int Userdata_InsertRecord(USERDATA *self,
	const char *machine,
	const char *login,
	const char *password
	);

#endif /* #ifndef USERDATA_H */


