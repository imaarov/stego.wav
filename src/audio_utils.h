#ifndef AUDIO_UTILS_H
#define AUDIO_UTILS_H

#include <stdio.h>

#include "wav_structures.h"

void print_wav_metadata(FILE *fp, WAVFmtSubChunk *fmt);

void read_pcm_data(FILE *fp, WAVFmtSubChunk *fmt, WAVDataSubChunk *data_chunk);
WAVHeader *getParsedHeader(FILE *fp);
WAVFmtSubChunk *getParsedFMT(FILE *fp);
WAVDataSubChunk *getDataChunk(FILE *fp);

#endif
