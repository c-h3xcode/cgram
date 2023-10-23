#ifndef CGRAM_TYPES_USER_H
#define CGRAM_TYPES_USER_H

#include <cJSON.h>
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

newtype(User) {
  int64_t id;
  bool is_bot;
  char *first_name;
  char *last_name;
  char *username;
  char *language_code;
  bool is_premium;
  bool added_to_attachment_menu;
  bool can_join_groups;
  bool can_read_all_group_messages;
  bool supports_inline_queries;
};
result_def(User);

type(User) * cgram_User_parse(cJSON *json);

cJSON *cgram_User_to_json(type(User) * user);

void cgram_User_free(type(User) * user);

#endif
