#ifndef CGRAM_TO_JSON_H
#define CGRAM_TO_JSON_H

#include <cJSON.h>
#include <stdbool.h>
#include <stdint.h>

#include "cgram.h"

int64_t _cgram_parse_int(cJSON *json, const char *key, cgram_error_t *error,
                         bool suppress_error);
int64_t *_cgram_parse_int_array(cJSON *json, const char *key,
                                cgram_error_t *error, bool suppress_error);
double _cgram_parse_double(cJSON *json, const char *key, cgram_error_t *error,
                           bool suppress_error);
char *_cgram_parse_string(cJSON *json, const char *key, cgram_error_t *error,
                          bool suppress_error);
char **_cgram_parse_string_array(cJSON *json, const char *key,
                                 cgram_error_t *error, bool suppress_error);
bool _cgram_parse_bool(cJSON *json, const char *key, cgram_error_t *error,
                       bool suppress_error);

cJSON *_cgram_to_json_int(int64_t value, bool );

#endif  // CGRAM_TO_JSON_H
