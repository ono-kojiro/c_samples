#ifndef ANY_SCANNER_H
#define ANY_SCANNER_H

#include <stdio.h>
#include "input.h"

#if 0
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
#endif

int AnyScanner_Scan(INPUT *s);

#endif /* #ifndef ANY_SCANNER_H */


