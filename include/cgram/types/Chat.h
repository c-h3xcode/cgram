#ifndef CGRAM_TYPES_CHAT_H
#define CGRAM_TYPES_CHAT_H

#include <cgram/types/ChatPhoto.h>
#include <cgram/types/User.h>
#include <stdint.h>

struct cgram_Chat {
  int64_t id;
  char *type;
  char *title;
  char *username;
  char *first_name;
  char *last_name;
  bool is_forum;
  cgram_ChatPhoto_t *photo;
  
};

#endif
