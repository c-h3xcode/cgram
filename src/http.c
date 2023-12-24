#define _GNU_SOURCE
#include <cgram/cgram.h>
#include <cgram/http.h>
#include <cgram/params.h>
#include <cgram/str.h>
#include <curl/curl.h>
#include <string.h>

#define TELEGRAM_API_BASEURL "https://api.telegram.org/bot%s/%s"

size_t _cgram_string_write_callback(void *ptr, size_t size, size_t nmemb,
                                    struct _cgram_string *str) {
  size_t new_len = str->length + size * nmemb;
  str->data = realloc(str->data, new_len + 1);
  if (str->data == NULL) {
    perror("realloc() failed");
    exit(EXIT_FAILURE);
  }
  memcpy(str->data + str->length, ptr, size * nmemb);
  str->data[new_len] = '\0';
  str->length = new_len;

  return size * nmemb;
}

void _cgram_init_curl_handle(cgram_handle_t *handle) {
  curl_easy_setopt(handle->_curl_easy_handle, CURLOPT_WRITEFUNCTION,
                   _cgram_string_write_callback);
}

_cgram_http_response_t _cgram_make_http_request(cgram_handle_t *handle,
                                                char *method,
                                                cJSON *fields) {
  char *url;
  asprintf(&url, TELEGRAM_API_BASEURL, handle->token, method);

  struct _cgram_string response;
  _cgram_string_init(&response);

  curl_easy_setopt(handle->_curl_easy_handle, CURLOPT_URL, url);
  curl_easy_setopt(handle->_curl_easy_handle, CURLOPT_WRITEDATA, &response);

  CURLcode result = curl_easy_perform(handle->_curl_easy_handle);

  free(url);
  free(params_str);

  _cgram_http_response_t http_response;
  http_response.code = result;
  http_response.data = response;

  return http_response;
}
