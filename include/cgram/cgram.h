#ifndef CGRAM_H
#define CGRAM_H

#define _GNU_SOURCE
#include <curl/curl.h>
#include <stdint.h>

#include "str.h"
#include "types.h"

typedef struct {
  CURL *_curl_easy_handle;
  CURLcode _curl_easy_perform_result;
  struct _cgram_string _raw_response;
  char *token;
} cgram_handle_t;

typedef enum {
  CGRAME_OK = 0,
  CGRAME_ERROR = 1,
} cgram_error_t;

#define CG_ENSURE(expr) if ((expr) != CGRAME_OK)

cgram_handle_t *cgram_handle_new(const char *token);
void cgram_handle_free(cgram_handle_t *handle);

cgram_error_t cgram_sendMessage(cgram_handle_t *handle, int64_t chat_id,
                                const char *text);

result(User) * cgram_getMe(cgram_handle_t *handle);

#endif
