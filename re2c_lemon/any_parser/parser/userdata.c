#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

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

int Userdata_OpenDatabase(USERDATA *self, const char *filepath)
{
	int ret;
	if(self->db){
		Userdata_CloseDatabase(self);	
	}

	ret = sqlite3_open_v2(filepath,
		&self->db,
		SQLITE_OPEN_READWRITE, NULL);
	if(ret != SQLITE_OK){
		fprintf(stderr, "ERROR : sqlite3_open() failed\n");
		return 1;
	}
	
	return 0;
}

int Userdata_CloseDatabase(USERDATA *self)
{
	int ret = SQLITE_OK;

	if(self->db){
		ret = sqlite3_close(self->db);
		if(ret != SQLITE_OK){
			fprintf(stderr, "ERROR : sqlite3_close() failed\n");
		}
		self->db = NULL;
	}
	return ret;
}

int Userdata_CreateTable(USERDATA *self)
{
	int ret;
	char *msg = NULL;

	ret = sqlite3_exec(self->db,
		"CREATE TABLE users_table ("
		"id INTEGER PRIMARY KEY, "
		"machine TEXT, "
		"login TEXT, "
		"password TEXT "
		");", NULL, NULL, &msg);

	if(ret != SQLITE_OK){
		fprintf(stderr, "ERROR : CREATE TABLE failed, %d, %s\n", ret, msg);
		sqlite3_free(msg);
		msg = NULL;
		ret = 1;
	}
	
	return ret;
}

int Userdata_DropTable(USERDATA *self)
{
	int ret;
	char *msg = NULL;

	if(!self->db){
		return 0;
	}

	ret = sqlite3_exec(self->db,
		"DROP TABLE IF EXISTS users_table;",
		NULL, NULL, &msg);

	if(ret != SQLITE_OK){
		fprintf(stderr, "%s\n", msg);
		sqlite3_free(msg);
		msg = NULL;
	}

	return 0;
}

int Userdata_InsertRecord(USERDATA *self,
	const char *machine,
	const char *login,
	const char *password
	)
{
	int ret;
	sqlite3_stmt *sth = NULL;
	
	ret = sqlite3_prepare_v2(self->db,
		"INSERT INTO users_table VALUES ( NULL, ?, ?, ? );",
		-1, &sth, NULL);
	if(ret != SQLITE_OK){
		fprintf(stderr, "ERROR : sqlite3_prepare_v2 failed\n");
		return 1;
	}

	sqlite3_bind_text(sth, 1, machine, strlen(machine), SQLITE_STATIC);
	sqlite3_bind_text(sth, 2, login, strlen(login), SQLITE_STATIC);
	sqlite3_bind_text(sth, 3, password, strlen(password), SQLITE_STATIC);
	while(1){
		ret = sqlite3_step(sth);
		if(ret == SQLITE_DONE){
			break;
		}
	}
	sqlite3_finalize(sth);
	return 0;
}


