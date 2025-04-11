#include "lsb_encoder.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int extract_lsb_message(unsigned char *pcm_data, size_t pcm_size, unsigned char *message_bits, size_t message_bits_len) {
    if (message_bits_len > pcm_size) {
        fprintf(stderr, "error: message is too large to extract.\n");
        return 0;
    }

    for (size_t i = 0; i < message_bits_len; ++i) {
        message_bits[i] = pcm_data[i] & 0x01;
    }

    return 1;
}