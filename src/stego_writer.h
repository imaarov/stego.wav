#ifndef STEGO_WRITER_H
#define STEGO_WRITER_H

#include <stdio.h>

#include "audio_utils.h"

int write_stego_wav(const char* output_filename, WAVHeader* header,
                    WAVFmtSubChunk* fmt, WAVDataSubChunk* data,
                    const unsigned char* modified_pcm_data);

#endif
