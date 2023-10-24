#include <cJSON.h>
#include <cgram/cgram.h>
#include <cgram/parser.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int64_t _cgram_parse_int(cJSON *json, const char *key, cgram_error_t *error,
                         bool suppress_error) {
  cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key);
  if (!cJSON_IsNumber(item)) {
    if (!suppress_error) {
      error->code = CGRAME_ERROR;
      error->origin = CGRAM_EORIGIN_CGRAM;
      error->description = "Parse error: expected number";
    }
    return 0;
  }
  return item->valuedouble;
}

int64_t *_cgram_parse_int_array(cJSON *json, const char *key,
                                cgram_error_t *error, bool suppress_error) {
  cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key);
  if (!cJSON_IsArray(item)) {
    if (!suppress_error) {
      error->code = CGRAME_ERROR;
      error->origin = CGRAM_EORIGIN_CGRAM;
      error->description = "Parse error: expected array";
    }
    return NULL;
  }
  int64_t *array = malloc(sizeof(int) * cJSON_GetArraySize(item));
  cJSON *element;
  int i = 0;
  cJSON_ArrayForEach(element, item) {
    array[i] = element->valuedouble;
    i++;
  }
  return array;
}

double _cgram_parse_double(cJSON *json, const char *key, cgram_error_t *error,
                           bool suppress_error) {
  cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key);
  if (!cJSON_IsNumber(item)) {
    if (!suppress_error) {
      error->code = CGRAME_ERROR;
      error->origin = CGRAM_EORIGIN_CGRAM;
      error->description = "Parse error: expected number";
    }
    return 0;
  }
  return item->valuedouble;
}

char *_cgram_parse_string(cJSON *json, const char *key, cgram_error_t *error,
                          bool suppress_error) {
  cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key);
  if (!cJSON_IsString(item)) {
    if (!suppress_error) {
      error->code = CGRAME_ERROR;
      error->origin = CGRAM_EORIGIN_CGRAM;
      error->description = "Parse error: expected string";
    }
    return NULL;
  }
  char *string = malloc(strlen(item->valuestring) + 1);
  strcpy(string, item->valuestring);
  return string;
}

char **_cgram_parse_string_array(cJSON *json, const char *key,
                                 cgram_error_t *error, bool suppress_error) {
  cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key);
  if (!cJSON_IsArray(item)) {
    if (!suppress_error) {
      error->code = CGRAME_ERROR;
      error->origin = CGRAM_EORIGIN_CGRAM;
      error->description = "Parse error: expected array";
    }
    return NULL;
  }
  char **array = malloc(sizeof(char *) * cJSON_GetArraySize(item));
  cJSON *element;
  int i = 0;
  cJSON_ArrayForEach(element, item) {
    array[i] = malloc(strlen(element->valuestring) + 1);
    strcpy(array[i], element->valuestring);
    i++;
  }
  return array;
}

bool _cgram_parse_bool(cJSON *json, const char *key, cgram_error_t *error,
                       bool suppress_error) {
  cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key);
  if (!cJSON_IsBool(item)) {
    if (!suppress_error) {
      error->code = CGRAME_ERROR;
      error->origin = CGRAM_EORIGIN_CGRAM;
      error->description = "Parse error: expected bool";
    }
    return false;
  }
  return item->valueint;
}
