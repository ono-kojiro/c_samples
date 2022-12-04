#include "config.h"

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inttypes.h>
#include "input.h"

int dump_input(INPUT *s)
{
	int i;
	fprintf(stderr, "token : '%.*s'",
		(int)(s->cur - s->tok), s->tok);
	fprintf(stderr, "ftell() is %d\n", s->in);
	fprintf(stderr, "tok : 0x%" PRIXPTR "\n", (uintptr_t)s->tok);
	fprintf(stderr, "cur : 0x%" PRIXPTR "\n", (uintptr_t)s->cur);
	fprintf(stderr, "lim : 0x%" PRIXPTR "\n", (uintptr_t)s->lim);
	fprintf(stderr, "eof : %d\n", s->eof);

	return 0;
}

INPUT *Input_Create()
{
	INPUT *s = (INPUT *)malloc(1 * sizeof(INPUT));
	memset(s, 0, 1 * sizeof(INPUT));
	return s;
}

int Input_Init(INPUT *s)
{
	if(s->buf){
		free(s->buf);
		s->buf = NULL;
	}
	s->buf = (unsigned char *)malloc(BUFSIZE+1);
	if(!s->buf){
		return 1;
	}

	s->lim = s->buf + BUFSIZE;
	s->cur = s->lim;
	s->mar = s->lim;
	s->tok = s->lim;
	s->eof = 0;

    s->lim[0] = 0;
    
	s->in  = stdin;
	s->out = stdout;

	return 0;
}

int fill(INPUT *s)
{
	size_t nread = 0;
    const size_t shift = s->tok - s->buf;
    const size_t used  = s->lim - s->tok;

    if (s->eof) {
        return 1;
    }

    if (shift < 1) {
        return 2;
    }
    memmove(s->buf, s->tok, used);
    s->lim -= shift;
    s->cur -= shift;
    s->mar -= shift;
    s->tok -= shift;
    nread = fread(s->lim, 1, BUFSIZE - used, s->in);
    s->lim += nread;

    s->lim[0] = 0;
    if(s->lim < s->buf + BUFSIZE){
        s->eof = 1;
    }
    return 0;
}

int Input_SetStream(INPUT *s, FILE *in, FILE *out)
{
    s->in = in;
    s->out  = out;
	return 0;
}

int Input_Delete(INPUT *s)
{
	if(s){
		if(s->buf){
			free(s->buf);
		}
		free(s);
	}
}

