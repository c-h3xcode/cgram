#include <cJSON.h>
#define _GNU_SOURCE
#include <cgram/http.h>
#include <cgram/params.h>
#include <cgram/parser.h>
#include <cgram/requests.h>
#include <stdlib.h>

_cgram_request_response_t _cgram_make_request(cgram_handle_t* handle,
                                              char* method,
                                              struct _cgram_params* params) {
  _cgram_http_response_t response =
      _cgram_make_http_request(handle, method, params);

  _cgram_request_response_t result;
  result.ok = true;
  cJSON* parsed_response = cJSON_Parse(response.data.data);

  result.ok = false;
  result.result_data = NULL;
  result.description = NULL;

  if (!cJSON_IsObject(parsed_response)) {
    goto end;
  }

  cJSON* status = cJSON_GetObjectItemCaseSensitive(parsed_response, "ok");
  if (cJSON_IsBool(status)) {
    result.ok = status->valueint;
  }

  cJSON* result_item =
      cJSON_GetObjectItemCaseSensitive(parsed_response, "result");
  if (cJSON_IsObject(result_item)) {
    result.result_data = result_item;
  }

  cJSON* description =
      cJSON_GetObjectItemCaseSensitive(parsed_response, "description");
  if (cJSON_IsString(description)) {
    result.description = description->valuestring;
  }

end:
  _cgram_string_free(&response.data);
  return result;
}

result(User) * cgram_getMe(cgram_handle_t* handle) {
  struct _cgram_params params;
  _cgram_params_init(&params);
  _cgram_request_response_t response =
      _cgram_make_request(handle, "getMe", &params);
  _cgram_params_free(&params);

  result(User)* user_result = malloc(sizeof(result(User)));

  if (!response.ok) {
    user_result->ok = false;
    user_result->contents.error.code = CGRAME_ERROR;
    user_result->contents.error.origin = CGRAM_EORIGIN_TELEGRAM;
    user_result->contents.error.description = response.description;
    return user_result;
  }

  cgram_error_t parse_error;

  type(User)* user = parse(User, response.result_data, parse_error) {
    user_result->ok = false;
    user_result->contents.error = parse_error;
    return user_result;
  };

  user_result->ok = true;
  user_result->contents.result = user;

  return user_result;
}

result(Message) *
    cgram_sendMessage(cgram_handle_t* handle, int64_t chat_id, char* text) {
  struct _cgram_params params;
  _cgram_params_init(&params);
  char* chat_id_string;
  asprintf(&chat_id_string, "%ld", chat_id);
  _cgram_params_add(&params, "chat_id", chat_id_string);
  _cgram_params_add(&params, "text", text);
  _cgram_request_response_t response =
      _cgram_make_request(handle, "sendMessage", &params);
  _cgram_params_free(&params);

  result(Message)* message_result = malloc(sizeof(result(Message)));

  if (!response.ok) {
    message_result->ok = false;
    message_result->contents.error.code = CGRAME_ERROR;
    message_result->contents.error.origin = CGRAM_EORIGIN_TELEGRAM;
    message_result->contents.error.description = response.description;
    return message_result;
  }

  cgram_error_t parse_error;

  type(Message)* message = parse(Message, response.result_data, parse_error) {
    message_result->ok = false;
    message_result->contents.error = parse_error;
    return message_result;
  };

  message_result->ok = true;
  message_result->contents.result = message;

  return message_result;
}
