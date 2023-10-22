#ifndef CGRAM_TYPES_H
#define CGRAM_TYPES_H

#include "types/User.h"
#include <stdbool.h>

typedef struct {
  bool ok;
  char *description;
} cgram_error_t;

#endif
