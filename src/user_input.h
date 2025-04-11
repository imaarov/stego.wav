#ifndef USER_INPUT_H
#define USER_INPUT_H

#define MAX_FILE_NAME_LEN 256
#define SECRET_MESSAGE_LEN 256

int get_file_name_from_user(char file_name[MAX_FILE_NAME_LEN]);

int check_file_type(const char *file_name);

int get_secret_message(char secret_message[SECRET_MESSAGE_LEN]);

#endif
