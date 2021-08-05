#ifndef USERDATA_H
#define USERDATA_H

typedef struct {
	int fd_port;
	int canonical_mode;
	int b_echo;
	int debug;
	SCANNER *scanner;
	int len;
	int buf_size;
	unsigned char buf[256];
} USERDATA;

USERDATA *create_userdata();
int destroy_userdata(USERDATA *self);

#endif /* #ifndef USERDATA_H */
