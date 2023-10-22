#ifndef CGRAM_HTTP_H
#define CGRAM_HTTP_H

#include <curl/curl.h>
#include <stdlib.h>

#include "cgram.h"
#include "params.h"
#include "str.h"

typedef struct {
  CURLcode code;
  struct _cgram_string data;
} _cgram_http_response_t;

void _cgram_init_curl_handle(cgram_handle_t *handle);

_cgram_http_response_t _cgram_make_http_request(cgram_handle_t *handle,
                                                char *method,
                                                struct _cgram_params *params);
#endif
