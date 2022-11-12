#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

#define RET(x) { \
	return (x); \
}

#if USE_PARSER
#else
enum {
	DEC = 1,
	WD,
	WS,
	EOL,
	HOST,
	MACHINE,
	LOGIN,
	PASSWORD,
	METHOD,
	FIELD_NAME,
	TCHAR,
	ANY
};
#endif

typedef struct _SCANNER
{
    unsigned char *buf;
    unsigned char *lim;
    unsigned char *cur;
    unsigned char *mar;
    unsigned char *tok;
    int eof;

    FILE *file;
	FILE *out;
}
SCANNER;

SCANNER *Scanner_Create();
int Scanner_Init(SCANNER *s);
int Scanner_SetInput(SCANNER *s, FILE *fp);
int Scanner_SetOutput(SCANNER *s, FILE *fp);
int Scanner_Scan(SCANNER *s);
int Scanner_Delete(SCANNER *s);

#endif /* #ifndef SCANNER_H */


