#ifndef CGRAM_REQUESTS_H
#define CGRAM_REQUESTS_H

#include <stdbool.h>

#include "cJSON.h"
#include "cgram.h"
#include "params.h"

typedef struct {
  bool ok;
  cJSON *result;
} _cgram_request_response_t;

_cgram_request_response_t _cgram_make_request(cgram_handle_t *handle,
                                              char *method,
                                              struct _cgram_params *params);
#endif
