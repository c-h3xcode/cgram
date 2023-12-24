#define _GNU_SOURCE
#include <cgram/params.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void _cgram_params_init(struct _cgram_params *params) {
  params->params = NULL;
  params->length = 0;
}

void _cgram_params_add(struct _cgram_params *params, const char *key,
                       const char *value) {
  params->params = realloc(params->params,
                           sizeof(struct _cgram_param) * (params->length + 1));
  params->params[params->length].key = strdup(key);
  params->params[params->length].value = strdup(value);
  params->length++;
}

void _cgram_params_add_int(struct _cgram_params *params, const char *key,
                           int value) {
  char *value_str;
  asprintf(&value_str, "%d", value);
  _cgram_params_add(params, key, value_str);
  free(value_str);
}

void _cgram_params_add_float(struct _cgram_params *params, const char *key,
                             float value) {
  char *value_str;
  asprintf(&value_str, "%f", value);
  _cgram_params_add(params, key, value_str);
  free(value_str);
}

void _cgram_params_add_bool(struct _cgram_params *params, const char *key,
                            bool value) {
  char *value_str;
  asprintf(&value_str, "%s", value ? "true" : "false");
  _cgram_params_add(params, key, value_str);
  free(value_str);
}

void _cgram_params_free(struct _cgram_params *params) {
  for (size_t i = 0; i < params->length; i++) {
    free(params->params[i].key);
    free(params->params[i].value);
  }
  free(params->params);
}

char *_cgram_params_to_string(struct _cgram_params *params) {
  char *params_str = malloc(1);
  params_str[0] = '\0';

  if (params->length == 0) {
    return params_str;
  }

  for (size_t i = 0; i < params->length; i++) {
    char *key = params->params[i].key;
    char *value = params->params[i].value;
    char *escaped_value = curl_easy_escape(NULL, value, 0);
    asprintf(&params_str, "%s%s=%s&", params_str, key, escaped_value);
    curl_free(escaped_value);
  }
  params_str[strlen(params_str) - 1] = '\0';
  return params_str;
}
