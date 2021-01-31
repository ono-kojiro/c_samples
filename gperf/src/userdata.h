#ifndef _USERDATA_H_
#define _USERDATA_H_

typedef struct _USERDATA
{
	char *name;
	int value;
	int write_value;
} USERDATA;

USERDATA *in_word_set(const char *str, size_t len);
USERDATA *get_userdata(const char *str, size_t len);

#endif /* #ifndef _USERDATA_H_ */



