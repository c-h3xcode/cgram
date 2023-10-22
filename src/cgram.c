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

  _cgram_string_init(&handle->_raw_response);
  _cgram_init_curl_handle(handle);

  return handle;
}

void cgram_handle_free(cgram_handle_t *handle) {
  curl_easy_cleanup(handle->_curl_easy_handle);
  free(handle->token);
  _cgram_string_free(&handle->_raw_response);
  free(handle);
}

cgram_error_t cgram_sendMessage(cgram_handle_t *handle, int64_t chat_id,
                                const char *text) {
  struct _cgram_params params;
  _cgram_params_init(&params);

  char *chat_id_str;
  asprintf(&chat_id_str, "%ld", chat_id);

  _cgram_params_add(&params, "chat_id", chat_id_str);
  _cgram_params_add(&params, "text", text);
  _cgram_params_add(&params, "parse_mode", "HTML");

  free(chat_id_str);

  // cgram_error_t result =
  //     _cgram_make_http_request(handle, "sendMessage", &params);

  _cgram_params_free(&params);

  printf("Response: %s\n", handle->_raw_response.data);

  _cgram_string_clear(&handle->_raw_response);
  return 0;
}

cgram_User_t *cgram_getMe(cgram_handle_t *handle) {
  struct _cgram_params params;
  _cgram_params_init(&params);

  _cgram_request_response_t response =
      _cgram_make_request(handle, "getMe", &params);

  _cgram_params_free(&params);

  if (!response.ok) {
    return NULL;
  }

  cgram_User_t *user = cgram_User_parse(response.result);
  return user;
}
