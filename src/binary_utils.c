#include "binary_utils.h"

#include <stdio.h>
#include <string.h>

void string_to_binary(const char *str, unsigned char *binary_data) {
  size_t str_len = strlen(str) + 1;
  for (size_t i = 0; i < str_len; ++i) {
    unsigned char byte = str[i];
    for (int bit = 7; bit >= 0; --bit) {
      binary_data[i * 8 + (7 - bit)] = (byte >> bit) & 1;
    }
  }
}

void binary_to_string(const unsigned char *binary_data, size_t binary_len, char *message) {
  size_t byte_idx = 0;
  size_t bit_idx = 0;
  unsigned char current_byte = 0;

  for (size_t i = 0; i < binary_len; ++i) {
    current_byte = (current_byte << 1) | binary_data[i];
    if (++bit_idx == 8) {
      message[byte_idx++] = current_byte;
      current_byte = 0;
      bit_idx = 0;
    }
  }

  if (bit_idx != 0) {
    message[byte_idx] = '\0';
  } else if (byte_idx == 0 || message[byte_idx-1] != '\0') {
    message[byte_idx] = '\0';
  }
}