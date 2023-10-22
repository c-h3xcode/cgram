#include <cJSON.h>
#include <cgram/types/User.h>
#include <stdlib.h>
#include <string.h>

cgram_User_t *cgram_User_parse(cJSON *json) {
  cgram_User_t *user = malloc(sizeof(cgram_User_t));

  user->id = 0;
  cJSON *id = cJSON_GetObjectItemCaseSensitive(json, "id");
  if (cJSON_IsNumber(id)) {
    user->id = id->valuedouble;
  }

  user->is_bot = 0;
  cJSON *is_bot = cJSON_GetObjectItemCaseSensitive(json, "is_bot");
  if (cJSON_IsBool(is_bot)) {
    user->is_bot = is_bot->valueint;
  }

  user->first_name = NULL;
  cJSON *first_name = cJSON_GetObjectItemCaseSensitive(json, "first_name");
  if (cJSON_IsString(first_name)) {
    user->first_name = malloc(strlen(first_name->valuestring) + 1);
    strcpy(user->first_name, first_name->valuestring);
  }

  user->last_name = NULL;
  cJSON *last_name = cJSON_GetObjectItemCaseSensitive(json, "last_name");
  if (cJSON_IsString(last_name)) {
    user->last_name = malloc(strlen(last_name->valuestring) + 1);
    strcpy(user->last_name, last_name->valuestring);
  }

  user->username = NULL;
  cJSON *username = cJSON_GetObjectItemCaseSensitive(json, "username");
  if (cJSON_IsString(username)) {
    user->username = malloc(strlen(username->valuestring) + 1);
    strcpy(user->username, username->valuestring);
  }

  user->language_code = NULL;
  cJSON *language_code =
      cJSON_GetObjectItemCaseSensitive(json, "language_code");
  if (cJSON_IsString(language_code)) {
    user->language_code = malloc(strlen(language_code->valuestring) + 1);
    strcpy(user->language_code, language_code->valuestring);
  }

  user->is_premium = 0;
  cJSON *is_premium = cJSON_GetObjectItemCaseSensitive(json, "is_premium");
  if (cJSON_IsBool(is_premium)) {
    user->is_premium = is_premium->valueint;
  }

  user->added_to_attachment_menu = 0;
  cJSON *added_to_attachment_menu =
      cJSON_GetObjectItemCaseSensitive(json, "added_to_attachment_menu");
  if (cJSON_IsBool(added_to_attachment_menu)) {
    user->added_to_attachment_menu = added_to_attachment_menu->valueint;
  }

  user->can_join_groups = 0;
  cJSON *can_join_groups =
      cJSON_GetObjectItemCaseSensitive(json, "can_join_groups");
  if (cJSON_IsBool(can_join_groups)) {
    user->can_join_groups = can_join_groups->valueint;
  }

  user->can_read_all_group_messages = 0;
  cJSON *can_read_all_group_messages =
      cJSON_GetObjectItemCaseSensitive(json, "can_read_all_group_messages");
  if (cJSON_IsBool(can_read_all_group_messages)) {
    user->can_read_all_group_messages = can_read_all_group_messages->valueint;
  }

  user->supports_inline_queries = 0;
  cJSON *supports_inline_queries =
      cJSON_GetObjectItemCaseSensitive(json, "supports_inline_queries");
  if (cJSON_IsBool(supports_inline_queries)) {
    user->supports_inline_queries = supports_inline_queries->valueint;
  }

  return user;
}

cJSON *cgram_User_to_json(cgram_User_t *user) {
  cJSON *json = cJSON_CreateObject();

  cJSON *id = cJSON_CreateNumber(user->id);
  cJSON_AddItemToObject(json, "id", id);

  cJSON *is_bot = cJSON_CreateBool(user->is_bot);
  cJSON_AddItemToObject(json, "is_bot", is_bot);

  cJSON *first_name = cJSON_CreateString(user->first_name);
  cJSON_AddItemToObject(json, "first_name", first_name);

  cJSON *last_name = cJSON_CreateString(user->last_name);
  cJSON_AddItemToObject(json, "last_name", last_name);

  cJSON *username = cJSON_CreateString(user->username);
  cJSON_AddItemToObject(json, "username", username);

  cJSON *language_code = cJSON_CreateString(user->language_code);
  cJSON_AddItemToObject(json, "language_code", language_code);

  cJSON *is_premium = cJSON_CreateBool(user->is_premium);
  cJSON_AddItemToObject(json, "is_premium", is_premium);

  cJSON *added_to_attachment_menu =
      cJSON_CreateBool(user->added_to_attachment_menu);
  cJSON_AddItemToObject(json, "added_to_attachment_menu",
                        added_to_attachment_menu);

  cJSON *can_join_groups = cJSON_CreateBool(user->can_join_groups);
  cJSON_AddItemToObject(json, "can_join_groups", can_join_groups);

  cJSON *can_read_all_group_messages =
      cJSON_CreateBool(user->can_read_all_group_messages);
  cJSON_AddItemToObject(json, "can_read_all_group_messages",
                        can_read_all_group_messages);

  cJSON *supports_inline_queries =
      cJSON_CreateBool(user->supports_inline_queries);
  cJSON_AddItemToObject(json, "supports_inline_queries",
                        supports_inline_queries);

  return json;
}

void cgram_User_free(cgram_User_t *user) {
  free(user->first_name);
  free(user->last_name);
  free(user->username);
  free(user->language_code);
  free(user);
}
