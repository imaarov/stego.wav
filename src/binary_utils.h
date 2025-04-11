#ifndef BINARY_UTILS_H
#define BINARY_UTILS_H

#include <stdlib.h>

void string_to_binary(const char *str, unsigned char *binary_data);
void binary_to_string(const unsigned char *binary_data, size_t binary_len, char *message);

#endif
