#ifndef CGRAM_TYPES_COMMON_H
#define CGRAM_TYPES_COMMON_H

#include "cgram.h"

#define result(T) cgram_##T##_result_t
#define type(T) cgram_##T##_t
#define _inner_type(T) struct cgram_##T
#define result_def(T)      \
  typedef struct {         \
    bool ok;               \
    union {                \
      type(T) * result;    \
      cgram_error_t error; \
    } contents;            \
  } result(T)

#define newtype(T)                  \
  typedef struct cgram_##T type(T); \
  struct cgram_##T

#define unwrap(T, error)             \
  T->ok ? T->contents.result : NULL; \
  error = T->contents.error;         \
  if (!T->ok)

#define parse_func(T) cgram_##T##_parse
#define parse_array_func(T) cgram_##T##_array_parse
#define parse_array_array_func(T) cgram_##T##_array_array_parse

#define parse(T, json, error)         \
  parse_func(T)(json, &error, false); \
  if (error.code != CGRAME_OK)

#define parse_func_def(T) \
  type(T) *               \
      parse_func(T)(cJSON * json, cgram_error_t * error, bool suppress_error)

#define parse_array_func_def(T)                                       \
  type(T) * *parse_array_func(T)(cJSON * json, cgram_error_t * error, \
                                 bool suppress_error)

#define parse_array_array_func_def(T)                                        \
  type(T) * **parse_array_array_func(T)(cJSON * json, cgram_error_t * error, \
                                        bool suppress_error)

#endif
