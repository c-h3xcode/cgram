#include <cgram/str.h>
#include <stdio.h>
#include <stdlib.h>

void _cgram_string_init(struct _cgram_string *string) {
  string->length = 0;
  string->data = malloc(string->length + 1);

  if (string->data == NULL) {
    perror("malloc() failed");
    exit(EXIT_FAILURE);
  }

  string->data[0] = '\0';
}

void _cgram_string_clear(struct _cgram_string *string) {
  string->length = 0;
  string->data[0] = '\0';
}

void _cgram_string_free(struct _cgram_string *string) {
  string->length = 0;
  free(string->data);
}
