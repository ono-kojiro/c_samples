#include "config.h"

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inttypes.h>

#define SIZE (64 * 1024)

enum {
  EOL = 1,
  WD = 2,
  DEC = 3,
  ANY = 4,
};

/*!max:re2c*/

#include "input.h"

/*!re2c re2c:define:YYCTYPE = "unsigned char"; */

int Simple_Scan(INPUT *s)
{
    unsigned long u;

	/* from submatch/http_rfc7230.re */

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
	SP  = ("u8"|"u"|"U"|"L");

    DBS = "\\\\"; // double backslash
	ES  = "\\"  ( [\'"?abfnrtv] | [0-7]{1,3} );
	BS  = "\x5C";  // backspace 0d92

    wd  = (A)+;
    dec = (D|NZ)+;

	any = [^];
*/


    for (;;) {
		s->tok = s->cur;
        /*!re2c
            re2c:yyfill:enable = 1;
            re2c:define:YYCURSOR = s->cur;
            re2c:define:YYMARKER = s->mar;
            re2c:define:YYLIMIT = s->lim;
            re2c:define:YYFILL = "fill(s) == 0;";
            re2c:define:YYFILL:naked = 1;
		*/

		/*!re2c
			eol {
				fprintf(stderr, "(EOL)\n");
				RET(EOL);
			}

			end {
				fprintf(stderr, "(EOF)\n");
				RET(EOF);
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
	}
}

