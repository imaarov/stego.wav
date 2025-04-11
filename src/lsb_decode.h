#ifndef LSB_DECODE_H
#define LSB_DECODE_H

#include <stdlib.h>

int extract_lsb_message(unsigned char *pcm_data, size_t pcm_size, 
    unsigned char *message_bits, size_t message_bits_len);

#endif