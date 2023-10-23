

#include <cgram/cgram.h>
#include <cgram/http.h>
#include <stdio.h>

#define BOT_TOKEN "6599693267:AAE7krZ_ZixWZAT1wb1uaHw7yblEFusZ5O8"

int main(int argc, char **argv) {
  cgram_handle_t *handle = cgram_handle_new(BOT_TOKEN);
  if (handle == NULL) {
    printf("Error creating handle\n");
    return 1;
  }

  result(User) *result = cgram_getMe(handle);
  if (result == NULL) {
    printf("Error getting user\n");
    return 1;
  }

  type(User) *user = unwrap(result) {
    printf("Error getting user: %s\n", result->description);
    return 1;
  }

  printf("Running as %s (@%s)\n", user->first_name, user->username);

  cgram_User_free(user);
  cgram_handle_free(handle);
  return 0;
}
