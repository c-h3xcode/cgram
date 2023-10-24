#include <cgram/cgram.h>
#include <cgram/http.h>
#include <cgram/requests.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <bot token> <chat_id>\n", argv[0]);
    return 1;
  }
  char *bot_token = argv[1];
  int64_t chat_id = atoi(argv[2]);

  cgram_error_t error;
  cgram_handle_t *handle = cgram_handle_new(bot_token);

  if (handle == NULL) {
    printf("Error creating handle\n");
    return 1;
  }

  result(User) *getMe_result = cgram_getMe(handle);
  if (getMe_result == NULL) {
    printf("Error getting user\n");
    return 1;
  }

  type(User) *user = unwrap(getMe_result, error) {
    printf("Error getting user: %s\n", error.description);
    return 1;
  }

  printf("Running as %s (@%s)\n", user->first_name, user->username);

  result(Message) *sendMessage_result =
      cgram_sendMessage(handle, chat_id, "Hello, world!");

  if (sendMessage_result == NULL) {
    printf("Error sending message\n");
    return 1;
  }

  type(Message) *message = unwrap(sendMessage_result, error) {
    printf("Error sending message: %s\n", error.description);
    return 1;
  }

  printf("Sent message '%s' to %s (@%s)\n", message->text,
         message->chat->first_name, message->chat->username);

  cgram_handle_free(handle);
  return 0;
}
