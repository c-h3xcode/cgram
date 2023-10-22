#ifndef CGRAM_STR_H
#define CGRAM_STR_H

#include <stdlib.h>

struct _cgram_string {
  char *data;
  size_t length;
};

void _cgram_string_init(struct _cgram_string *string);

void _cgram_string_clear(struct _cgram_string *string);

void _cgram_string_free(struct _cgram_string *string);

#endif
