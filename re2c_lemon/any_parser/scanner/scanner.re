#include "config.h"

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inttypes.h>

/*!max:re2c*/
#define SIZE (64 * 1024)

#include "scanner.h"

#if USE_PARSER
#include "parser.h"
#endif

#define PRINT_TOKEN(x) { \
	fprintf(stderr, "(%s:", x); \
	fprintf(stderr, "%.*s", (int)(s->cur - s->tok), s->tok); \
	fprintf(stderr, ")"); \
}

int dump_scanner(SCANNER *s)
{
	int i;
	fprintf(stderr, "token : '%.*s'",
		(int)(s->cur - s->tok), s->tok);
	fprintf(stderr, "ftell() is %d\n", s->file);
	fprintf(stderr, "tok : 0x%" PRIXPTR "\n", (uintptr_t)s->tok);
	fprintf(stderr, "cur : 0x%" PRIXPTR "\n", (uintptr_t)s->cur);
	fprintf(stderr, "lim : 0x%" PRIXPTR "\n", (uintptr_t)s->lim);
	fprintf(stderr, "eof : %d\n", s->eof);

	return 0;
}

int fill(SCANNER *s, size_t need)
{
	size_t nread = 0;
    size_t free;

#if DEBUG
	fprintf(stderr, "%s:%d:%s: ",
		__FILE__ , __LINE__ , __FUNCTION__ );
	fprintf(stderr, "fill() is called\n");
#endif

    if (s->eof) {
#if DEBUG
		fprintf(stderr, "%s:%d:%s: ",
			__FILE__ , __LINE__ , __FUNCTION__ );
		dump_scanner(s);
#endif
		if(s->cur < s->lim - YYMAXFILL){
			fprintf(stderr, "but continue\n");
			return 1;
		}
		else {
			dump_scanner(s);
			fprintf(stderr, "s->eof\n");
		}
        return 0;
    }
    
	free = s->tok - s->buf;

#if DEBUG
	fprintf(stderr, "DEBUG : %s(%d) in%s, fill, free is %d, need = %d\n",
		__FILE__ , __LINE__ , __FUNCTION__ ,
		free, need	
		);
#endif
    if (free < need) {
#if DEBUG
		fprintf(stderr, "%s(%d) in %s\n",
			__FILE__ , __LINE__ , __FUNCTION__ );
		fprintf(stderr, "free < need\n");
#endif
        return 0;
    }
    memmove(s->buf, s->tok, s->lim - s->tok);
    s->lim -= free;
    s->cur -= free;
    s->mar -= free;
    s->tok -= free;
    nread = fread(s->lim, 1, free, s->file);
    s->lim += nread;
    if (s->lim < s->buf + SIZE) {
#if DEBUG
		fprintf(stderr, "%s(%d) in %s\n",
			__FILE__ , __LINE__ , __FUNCTION__ );
		fprintf(stderr, "read %d bytes from file\n", nread);
		fprintf(stderr, "set s->eof 1\n");
#endif
        s->eof = 1;
        memset(s->lim, 0, YYMAXFILL);
        s->lim += YYMAXFILL;
    }
    return 1;
}

SCANNER *Scanner_Create()
{
	SCANNER *s = (SCANNER *)malloc(1 * sizeof(SCANNER));
	memset(s, 0, 1 * sizeof(SCANNER));
#if DEBUG
	fprintf(stderr, "SCANNER : Scanner_Create()\n");
#endif

	return s;
}

int Scanner_Init(SCANNER *s)
{
	if(s->buf){
		free(s->buf);
		s->buf = NULL;
	}
	s->buf = (unsigned char *)malloc(SIZE + YYMAXFILL);
	if(!s->buf){
		return 1;
	}

	s->lim = s->buf + SIZE;
	s->cur = s->lim;
	s->mar = s->lim;
	s->tok = s->lim;
	s->eof = 0;
	s->file = stdin;
	s->out = stdout;

#if DEBUG
	fprintf(stderr, "SCANNER : Scanner_Init\n");
#endif
	return 0;
}

int Scanner_SetInput(SCANNER *s, FILE *fp)
{
	s->file = fp;
#if DEBUG
	fprintf(stderr, "SCANNER : Scanner_SetInput()\n");
#endif
	return 0;
}

int Scanner_SetOutput(SCANNER *s, FILE *fp)
{
	s->out = fp;
#if DEBUG
	fprintf(stderr, "SCANNER : Scanner_SetOutput()\n");
#endif
	return 0;
}


/*!re2c re2c:define:YYCTYPE = "unsigned char"; */

int Scanner_Scan(SCANNER *s)
{
    unsigned long u;

	/* from submatch/http_rfc7230.re */

#if DEBUG
	fprintf(stderr, "SCANNER : Scanner_Scan() start\n");
#endif

/*!re2c
    end = "\x00";
    eol = ([\r\n]|[\n]);
    ws  = [ \t\v]+;

    O   = [0-7];         // oct
    D   = [0-9];         // digit
    NZ  = [1-9];         // non-zero
    L   = [a-zA-Z_];     // letter
    A   = [a-zA-Z_0-9];  // alphabet
    H   = [a-fA-F0-9];   // hex
    HP  = "0" [xX];      // hex prefix
    E   = [Ee][+-]?D+;
    P   = [Pp][+-]?D+;
    FS  = ("f"|"F"|"l"|"L");     // float suffix
    IS  = ((("u"|"U")("l"|"L"|"ll"|"LL")?)|(("l"|"L"|"ll"|"LL")("u"|"U")?));
    CP  = ("u"|"U"|"L");

	ES  = "\\"  ( ['"?abfnrtv] | [0-7]{1,3} );
	BS  = "\x5C";  // backspace 0d92

    wd  = (A)+;
    dec = (D|NZ)+;

	any = [^];
*/


    for (;;) {
std:
		s->tok = s->cur;
#if DEBUG
		fprintf(stderr, "%s:%d:%s: ",
			__FILE__ , __LINE__ , __FUNCTION__ );
		fprintf(stderr, "for loop\n");
#endif
        /*!re2c
            re2c:yyfill:enable = 1;
            re2c:define:YYCURSOR = s->cur;
            re2c:define:YYMARKER = s->mar;
            re2c:define:YYLIMIT = s->lim;
            re2c:define:YYFILL = "if (!fill(s, @@)) return EOF;";
            re2c:define:YYFILL:naked = 1;
		*/


		/*!re2c
			"/*" {
				goto comment_c;
			}
			
			"#" {
				goto comment_perl;
			}
			
			"//" {
				goto comment_cxx;
			}

			eol {
				fprintf(stderr, "(EOL)\n");
				continue;
			}

			end {
				fprintf(stderr, "(EOF)\n");
				RET(EOF);
			}

			BS {
				PRINT_TOKEN("BACKSLASH");
				RET(BACKSLASH);
			}

			CP? "'" ([^']|ES|BS)+ "'" {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}
			
			(HP) (H)+ (IS)? {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			NZ D* IS? {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			"0" D* IS? {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			D* "." D+ E? FS? {
				PRINT_TOKEN("F_CONSTANT");
				RET(F_CONSTANT);
			}

			dec {
				PRINT_TOKEN("DEC");
				RET(DEC);
			}
			
			wd {
				PRINT_TOKEN("WD");
				RET(WD);
			}

			ws {
				fprintf(stderr, "%.*s",
					(int)(s->cur - s->tok), s->tok);
				continue;
			}
			
			any {
				PRINT_TOKEN("ANY");
				RET(ANY);
			}
			
			* {
				fprintf(stderr, "(UNKNOWN:%X)", s->tok[0]);
				RET(-1);
			}
		*/

comment_c :
		/*!re2c

			"*/" {
				goto std;
			}

			end {
				fprintf(stderr, "\nERROR : unterminated comment\n");
				exit(1);
			}

			* {
				goto comment_c;
			}

		*/

comment_perl :
		/*!re2c
			eol {
				fprintf(stderr, "(EOL)\n");
				goto std;
			}

			end {
				fprintf(stderr, "\nERROR : unterminated comment\n");
				exit(1);
			}

			* {
				goto comment_perl;
			}

		*/

comment_cxx :
		/*!re2c
			eol {
				fprintf(stderr, "(EOL)\n");
				goto std;
			}

			end {
				fprintf(stderr, "\nERROR : unterminated comment\n");
				exit(1);
			}

			* {
				goto comment_cxx;
			}

		*/


	}

}

int Scanner_Delete(SCANNER *s)
{
	if(s){
		if(s->buf){
			free(s->buf);
		}
		free(s);
	}
}

