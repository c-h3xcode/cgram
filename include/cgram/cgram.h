#ifndef CGRAM_H
#define CGRAM_H

#define _GNU_SOURCE
#include <curl/curl.h>
#include <stdint.h>

#include "str.h"

typedef struct {
  CURL *_curl_easy_handle;
  CURLcode _curl_easy_perform_result;
  char *token;
} cgram_handle_t;

enum cgram_error_code {
  CGRAME_OK = 0,
  CGRAME_ERROR = 1,
};

enum cgram_error_origin {
  CGRAM_EORIGIN_TELEGRAM = 0,
  CGRAM_EORIGIN_CGRAM = 1,
};

typedef struct {
  enum cgram_error_code code;
  enum cgram_error_origin origin;
  char *description;
} cgram_error_t;

#define CG_ENSURE(expr) if ((expr) != CGRAME_OK)

cgram_handle_t *cgram_handle_new(const char *token);
void cgram_handle_free(cgram_handle_t *handle);

#include "types.h"

#endif
