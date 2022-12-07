// re2c $INPUT -o $OUTPUT
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#
/*!max:re2c*/
#define BUFSIZE (4096 - YYMAXFILL)

struct Input {
    FILE *file;
    char buf[BUFSIZE + YYMAXFILL], *lim, *cur, *tok, *mar;
    int eof;
};

static int fill(struct Input *in, size_t need) {
    if (in->eof) return 1;

    const size_t shift = in->tok - in->buf;
    const size_t used = in->lim - in->tok;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < need) return 2;

    // Shift buffer contents (discard everything up to the current token).
    memmove(in->buf, in->tok, used);
    in->lim -= shift;
    in->cur -= shift;
    in->tok -= shift;
    in->mar -= shift;

    // Fill free space at the end of buffer with new data from file.
    in->lim += fread(in->lim, 1, BUFSIZE - used, in->file);

    // If read less than expected, this is end of input => add zero padding
    // so that the lexer can access characters at the end of buffer.
    if (in->lim < in->buf + BUFSIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }

    return 0;
}

static int lex(struct Input *in) {
    int count = 0;
	//fprintf(stderr, "%s(%d) : lex start\n", __FILE__ , __LINE__ );
    for (;;) {
        in->tok = in->cur;
    /*!re2c
        re2c:yyfill:enable = 1;
        re2c:define:YYCTYPE  = char;
        re2c:define:YYCURSOR = in->cur;
        re2c:define:YYMARKER = in->mar;
        re2c:define:YYLIMIT  = in->lim;
        re2c:define:YYFILL   = "if (fill(in, @@) != 0) return -1;";


        end = "\x00";
        str = ['] ([^'\\] | [\\][^])* ['];
        id  = [a-zA-Z_][a-zA-Z_0-9]*;
        ws  = [ \t\v]+;
        nl  = ( "\x0D\x0A" | "\x0D" | "\x0A" );

        oct = "0" [0-7]*;
        dec = [1-9][0-9]*;
        hex = "0x" [0-9a-fA-F]+;

        plan = "1.." dec;
        testpoint = ("not ")? "ok";

        end {
            fprintf(stderr, " (END) ");
            fprintf(stderr, "\n");
            RET(END);
        }

        plan {
            fprintf(stderr, " (PLAN) ");
            RET(PLAN);
        }

        testpoint {
            fprintf(stderr, " (TESTPOINT) ");
            RET(TESTPOINT);
        }

        nl {
            RET(NL);
        }

        ws {
            continue;
        }

        nl {
            fprintf(stderr, " (NL)\n");
            RET(NL);
        }

        * {
           fprintf(stderr, " (ANY:%.*s) ", in->cur - in->tok, in->tok);
           RET(ANY);
        }
    */
    }
}

SCANNER *Scanner_Create()
{
  struct Input *self = NULL;
  self = (struct Input *)malloc(1 * sizeof(struct Input));
  memset(self, 0, sizeof(struct Input));

  return (SCANNER *)self;
}

int Scanner_Delete(SCANNER *s)
{
  free(s);
}

int Scanner_Init(SCANNER *s)
{
  struct Input *self = (struct Input *)s;
  self->cur = self->tok = self->lim = self->buf + BUFSIZE;
  self->eof = 0;
  if(self->file){
    fclose(self->file);
  }
  self->file = NULL;
  return 0;
}

int Scanner_Open(SCANNER *s, const char *filename)
{
  int ret = 0;
  struct Input *self = (struct Input *)s;
  if(self->file){
    fclose(self->file);
  }
  self->file = fopen(filename, "r");
  if(!self->file){
    fprintf(stderr, "ERROR : can not open %s\n", filename);
	ret = 1;
  }

  return ret;
}

int Scanner_GetBufSize(SCANNER *s)
{
  return BUFSIZE;
}

int Scanner_Scan(SCANNER *s, int *id)
{
  int retval;

  struct Input *self = (struct Input *)s;
  retval = lex(self);
  *id = retval;

  if(retval == ANY){
    retval = 1;
  }
  else if(retval == END){
    retval = -1;
  }
  else {
    retval = 0;
  }

  return retval;
}

#if 0
int main() {
    const char *fname = "input";
    const char content[] = "'qu\0tes' 'are' 'fine: \\'' ";

    // Prepare input file: a few times the size of the buffer, containing
    // strings with zeroes and escaped quotes.
    FILE *f = fopen(fname, "w");
    for (int i = 0; i < BUFSIZE; ++i) {
        fwrite(content, 1, sizeof(content) - 1, f);
    }
    fclose(f);
    int count = 3 * BUFSIZE; // number of quoted strings written to file

    // Initialize lexer state: all pointers are at the end of buffer.
    // This immediately triggers YYFILL, as the check `in.cur < in.lim` fails.
    struct Input in;
    in.file = fopen(fname, "r");
    in.cur = in.tok = in.lim = in.buf + BUFSIZE;
    in.eof = 0;

    // Run the lexer.
    assert(lex(&in) == count);

    // Cleanup: remove input file.
    fclose(in.file);
    remove(fname);
    return 0;
}
#endif
