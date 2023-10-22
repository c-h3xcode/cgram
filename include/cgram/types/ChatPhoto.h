#ifndef CGRAM_TYPES_CHATPHOTO_H
#define CGRAM_TYPES_CHATPHOTO_H

struct cgram_ChatPhoto {
  char *small_file_id;
  char *small_file_unique_id;
  char *big_file_id;
  char *big_file_unique_id;
};

typedef struct cgram_ChatPhoto cgram_ChatPhoto_t;

#endif
