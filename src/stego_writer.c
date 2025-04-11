#include "stego_writer.h"

#include <stdlib.h>
#include <string.h>

int write_stego_wav(const char* output_filename, WAVHeader* header,
                    WAVFmtSubChunk* fmt, WAVDataSubChunk* data,
                    const unsigned char* modified_pcm_data) {
  FILE* out_fp = fopen(output_filename, "wb");
  if (!out_fp) {
    fprintf(stderr, "Error: Cannot open output file '%s'\n", output_filename);
    return 0;
  }

  fwrite(header, sizeof(WAVHeader), 1, out_fp);

  fwrite(fmt, sizeof(WAVFmtSubChunk), 1, out_fp);

  fwrite(data, sizeof(char), 8, out_fp);

  fwrite(modified_pcm_data, sizeof(unsigned char), data->data_size, out_fp);

  fclose(out_fp);
  return 1;
}