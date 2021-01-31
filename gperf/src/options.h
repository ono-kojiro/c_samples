#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct _OPTION
{
	char *name;
	char *value;
} OPTION;

OPTION *get_option(const char *str, size_t len);
int set_option(const char *key, const char *val);

OPTION *get_options_word_array(int id);

int get_length_of_options_word_array();
int print_options();
int free_options();

#endif /* #ifndef OPTIONS_H */



