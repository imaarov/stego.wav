#include "user_input.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_secret_message(char secret_message[SECRET_MESSAGE_LEN]) {
  printf("enter your secret message: \n");
  if (fgets(secret_message, SECRET_MESSAGE_LEN, stdin) == NULL) {
    fprintf(stderr, "error while reading the secret message from stdin\n");
    return -1;
  }
  secret_message[strcspn(secret_message, "\n")] =
      0;
  return 1;
}

int get_file_name_from_user(char file_name[MAX_FILE_NAME_LEN]) {
  printf("enter the audio file name: ");

  if (fgets(file_name, MAX_FILE_NAME_LEN, stdin) == NULL) {
    fprintf(stderr, "error reading filename from terminal\n");
    return -1;
  }

  file_name[strcspn(file_name, "\n")] = 0;

  if (check_file_type(file_name) == -1) {
    return -1;
  }
  return 1;
}

int check_file_type(const char *file_name) {
  char lower_file_name[MAX_FILE_NAME_LEN];
  for (int i = 0; file_name[i]; i++) {
    lower_file_name[i] = tolower(file_name[i]);
  }
  lower_file_name[strlen(file_name)] = '\0';

  if (strstr(lower_file_name, ".wav") == NULL) {
    fprintf(stderr, "cant handle this file extension right now.\n");
    return -1;
  }
  return 1;
}
