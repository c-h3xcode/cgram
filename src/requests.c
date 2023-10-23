#include <cJSON.h>
#include <cgram/http.h>
#include <cgram/params.h>
#include <cgram/requests.h>

_cgram_request_response_t _cgram_make_request(cgram_handle_t* handle,
                                              char* method,
                                              struct _cgram_params* params) {
  _cgram_http_response_t response =
      _cgram_make_http_request(handle, method, params);

  _cgram_request_response_t result;
  result.ok = true;
  cJSON* parsed_response = cJSON_Parse(response.data.data);

  result.ok = false;
  result.result = NULL;
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
    result.result = result_item;
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
