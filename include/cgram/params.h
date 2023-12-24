#ifndef CGRAM_PARAMS_H
#define CGRAM_PARAMS_H

#include <stdbool.h>
#include <stdlib.h>

struct _cgram_param {
  char *key;
  char *value;
};

struct _cgram_params {
  struct _cgram_param *params;
  size_t length;
};

void _cgram_params_init(struct _cgram_params *params);

void _cgram_params_add(struct _cgram_params *params, const char *key,
                       const char *value);

void _cgram_params_add_int(struct _cgram_params *params, const char *key,
                           int value);

void _cgram_params_add_float(struct _cgram_params *params, const char *key,
                             float value);

void _cgram_params_add_bool(struct _cgram_params *params, const char *key,
                            bool value);

char *_cgram_params_to_string(struct _cgram_params *params);

void _cgram_params_free(struct _cgram_params *params);

#endif
