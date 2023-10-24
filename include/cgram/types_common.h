#ifndef CGRAM_TYPES_COMMON_H
#define CGRAM_TYPES_COMMON_H

#define result(T) cgram_##T##_result_t
#define type(T) cgram_##T##_t
#define _inner_type(T) struct cgram_##T
#define result_def(T)  \
  typedef struct {     \
    bool ok;           \
    type(T) * result;  \
    char *description; \
  } result(T)

#define newtype(T)                  \
  typedef struct cgram_##T type(T); \
  struct cgram_##T

#define unwrap(T)           \
  T->ok ? T->result : NULL; \
  if (!T->ok)

#endif
