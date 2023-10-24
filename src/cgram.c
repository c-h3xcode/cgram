#define _GNU_SOURCE
#include <cJSON.h>
#include <cgram/cgram.h>
#include <cgram/http.h>
#include <cgram/requests.h>
#include <cgram/str.h>
#include <cgram/types.h>
#include <curl/curl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cgram_handle_t *cgram_handle_new(const char *token) {
  cgram_handle_t *handle = malloc(sizeof(cgram_handle_t));
  handle->_curl_easy_handle = curl_easy_init();
  handle->token = malloc(strlen(token) + 1);
  strcpy(handle->token, token);
  _cgram_init_curl_handle(handle);

  return handle;
}

void cgram_handle_free(cgram_handle_t *handle) {
  curl_easy_cleanup(handle->_curl_easy_handle);
  free(handle->token);
  free(handle);
}
