#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

#define BUFSIZE 4096

#define RET(x) { \
	return (x); \
}

#define PRINT_TOKEN(x) { \
	fprintf(stderr, "(%s:", x); \
	fprintf(stderr, "%.*s", (int)(s->cur - s->tok), s->tok); \
	fprintf(stderr, ")"); \
}

typedef struct
{
    unsigned char *buf;
    unsigned char *lim;
    unsigned char *cur;
    unsigned char *mar;
    unsigned char *tok;
    int eof;

    FILE *in;
	FILE *out;
}
INPUT;

INPUT *Input_Create();
int Input_Init(INPUT *s);
int Input_SetStream(INPUT *s, FILE *in, FILE *out);
int Input_Delete(INPUT *s);
int fill(INPUT *s);

#endif /* #ifndef INPUT_H */


