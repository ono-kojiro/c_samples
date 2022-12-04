#ifndef STR_H
#define STR_H

typedef struct _STR {
  char *s;
} STR;

STR *create_str(const char *str, int len);
void delete_str(STR *self);
int set_str(STR *self, const char *str);

#endif /* #ifndef STR_H */

