#ifndef _SCANNER_H_
#define _SCANNER_H_

#define RET(x) { return x; }

enum {
  ANY = 0,
  END,
  ID,
  STR,
  OCT,
  DEC,
  HEX,
  WS,
  NL
};

typedef struct {
  int n;
} SCANNER;

SCANNER *Scanner_Create();
int Scanner_Delete(SCANNER *s);
int Scanner_Init(SCANNER *s);
int Scanner_Open(SCANNER *s, const char *filename);
int Scanner_GetBufSize(SCANNER *s);
int Scanner_Scan(SCANNER *s, int *id);

#endif /* #ifndef _SCANNER_H_ */

