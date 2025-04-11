#ifndef LSB_ENCODER_H
#define LSB_ENCODER_H

#include <stddef.h>

// embeds the binary message into the PCM data buffer using LSB steganography
// pcm_data        : pointer to raw PCM bytes
// pcm_size        : size of the PCM data buffer
// message_bits    : binary form of the secret message (array of 0s and 1s)
// message_bits_len: number of bits in message_bits
// returns: 1 on success, 0 on failure (e.g., message too large)
int embed_lsb_message(unsigned char *pcm, size_t pcm_size,
                   const unsigned char *message_bits, size_t message_bits_len);

#endif
