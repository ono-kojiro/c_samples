#ifndef _BAUDRATE_H_
#define _BAUDRATE_H_

typedef struct _BAUDRATE
{
	char *name;
	int value;
	int flag;
} BAUDRATE;

//BAUDRATE *in_word_set(const char *str, size_t len);
//BAUDRATE *get_baudrate(const char *str, size_t len);

int get_baudrate_flag(const char *str);

#endif /* #ifndef _BAUDRATE_H_ */



