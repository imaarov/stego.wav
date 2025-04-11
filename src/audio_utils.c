#include "audio_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_wav_metadata(FILE *fp, WAVFmtSubChunk *fmt) {
  printf("Audio Format: %u (1 = PCM)\n", fmt->audio_format);
  printf("Number of Channels: %u\n", fmt->num_channels);
  printf("Sample Rate: %u Hz\n", fmt->sample_rate);
  printf("Bits per Sample: %u\n", fmt->bits_per_sample);
  printf("Byte Rate: %u\n", fmt->byte_rate);
  printf("Block Align: %u\n", fmt->block_align);

  if (fmt->fmt_size > sizeof(WAVFmtSubChunk) - 8) {
    fseek(fp, fmt->fmt_size - (sizeof(WAVFmtSubChunk) - 8), SEEK_CUR);
  }
}

WAVHeader *getParsedHeader(FILE *fp) {
  WAVHeader *header = (WAVHeader *)malloc(sizeof(WAVHeader));
  if (fread(header, sizeof(WAVHeader), 1, fp) != 1 ||
      strncmp(header->riff, "RIFF", 4) != 0 ||
      strncmp(header->wave, "WAVE", 4) != 0) {
    fprintf(stderr, "nnot a valid WAV file.\n");
    return NULL;
  }
  return header;
}

WAVFmtSubChunk *getParsedFMT(FILE *fp) {
  WAVFmtSubChunk *fmt = (WAVFmtSubChunk *)malloc(sizeof(WAVFmtSubChunk));
  if (fread(fmt, sizeof(WAVFmtSubChunk), 1, fp) != 1 ||
      strncmp(fmt->fmt, "fmt ", 4) != 0) {
    fprintf(stderr, "error reading fmt chunk.\n");
    return NULL;
  }
  return fmt;
}

WAVDataSubChunk *getDataChunk(FILE *fp) {
  WAVDataSubChunk *data_chunk =
      (WAVDataSubChunk *)malloc(sizeof(WAVDataSubChunk));
  while (1) {
    if (fread(data_chunk, 8, 1, fp) != 1) {
      fprintf(stderr, "error finding data chunk.\n");
      return NULL;
    }

    if (strncmp(data_chunk->data, "data", 4) == 0) {
      printf("data Chunk Size: %u bytes\n", data_chunk->data_size);
      break;
    } else {
      fseek(fp, data_chunk->data_size, SEEK_CUR);
    }
  }
  data_chunk->pcm_data = (unsigned char *)malloc(data_chunk->data_size);
  if (fread(data_chunk->pcm_data, 1, data_chunk->data_size, fp) !=
      data_chunk->data_size) {
    fprintf(stderr, "error reading PCM data.\n");
    free(data_chunk->pcm_data);
    free(data_chunk);
    return NULL;
  }
  return data_chunk;
}

void read_pcm_data(FILE *fp, WAVFmtSubChunk *fmt, WAVDataSubChunk *data_chunk) {
  size_t sample_size = fmt->bits_per_sample / 8;
  size_t samples_to_read = data_chunk->data_size / sample_size;

  for (size_t i = 0; i < samples_to_read; i++) {
    unsigned char sample[sample_size];
    if (fread(sample, sample_size, 1, fp) != 1) {
      fprintf(stderr, "error reading PCM sample %zu.\n", i);
      return;
    }

    printf("sample %zu (binary): ", i);
    for (size_t j = 0; j < sample_size; ++j) {
      for (int bit = 7; bit >= 0; --bit) {
        printf("%d", (sample[j] >> bit) & 1);
      }
      printf(" ");
    }
    printf("\n");
  }
}
