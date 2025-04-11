#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef struct {
  char riff[4];
  uint32_t file_size;
  char wave[4];
} WAVHeader;

typedef struct {
  char fmt[4];
  uint32_t fmt_size;
  uint16_t audio_format;
  uint16_t num_channels;
  uint32_t sample_rate;
  uint32_t byte_rate;
  uint16_t block_align;
  uint16_t bits_per_sample;
} WAVFmtSubChunk;

typedef struct {
  char data[4];
  uint32_t data_size;
  unsigned char* pcm_data;
} WAVDataSubChunk;

#endif
