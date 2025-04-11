#include "lsb_encoder.h"

#include <stdio.h>

int embed_lsb_message(unsigned char *pcm_data, size_t pcm_size,
                      const unsigned char *message_bits,
                      size_t message_bits_len) {
  if (message_bits_len > pcm_size) {
    fprintf(stderr, "error: message is too long to embed in the audio.\n");
    return 0;
  }

  for (size_t i = 0; i < message_bits_len; ++i) {
    pcm_data[i] &= 0xFE;
    pcm_data[i] |= (message_bits[i] & 0x01);
  }

  return 1;
}
