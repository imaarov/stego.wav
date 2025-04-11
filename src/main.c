#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audio_utils.h"
#include "binary_utils.h"
#include "stego_writer.h"
#include "user_input.h"
#include "lsb_encoder.h"
#include "lsb_decode.h"

#define MAX_FILE_NAME_LEN 256
#define SECRET_MESSAGE_LEN 256

int encode();
void decode();

int main() {
  int choice;

  printf("steganography tool\n");
  printf("1. encode a message into an audio file\n");
  printf("2. decode a message from a stego audio file\n");
  printf("enter your choice: ");
  scanf("%d", &choice);
  getchar();

  if (choice == 1) {
      encode();
  } else if (choice == 2) {
      decode();
  } else {
      printf("not a choice...\n");
  }

  return 0;
}

int encode() {
  char file_name[MAX_FILE_NAME_LEN];
  if (get_file_name_from_user(file_name) != 1) {
    return 1;
  }

  char secret_message[SECRET_MESSAGE_LEN];
  if (get_secret_message(secret_message) != 1) {
    return -1;
  }

  // add 1 for the null terminator '\0' 
  // (include this that is not include in default strlen behaviour)
  uint32_t message_len = strlen(secret_message) + 1;
  // binary buffer, represent the message
  unsigned char binary_data[SECRET_MESSAGE_LEN * 8];
  for (int bit = 31; bit >= 0; --bit) {
    binary_data[31 - bit] = (message_len >> bit) & 1;
  }
  string_to_binary(secret_message, binary_data + 32);

  FILE* fp = fopen(file_name, "rb");
  if (!fp) {
    fprintf(stderr, "error reading the file.\n");
    return -1;
  }

  WAVHeader* header = getParsedHeader(fp);
  WAVFmtSubChunk* fmt = getParsedFMT(fp);
  print_wav_metadata(fp, fmt);
  WAVDataSubChunk* data = getDataChunk(fp);

  size_t message_bits_len = 32 + message_len * 8;
  if (!embed_lsb_message(data->pcm_data, data->data_size, binary_data, message_bits_len)) {
    fprintf(stderr, "message too long for this audio.\n");
    free(header);
    free(fmt);
    free(data);
    fclose(fp);
    return 1;
  }

  if (!write_stego_wav("stego_output.wav", header, fmt, data, data->pcm_data)) {
    fprintf(stderr, "failed to write stego WAV.\n");
    free(header);
    free(fmt);
    free(data);
    fclose(fp);
    return 1;
  }

  fclose(fp);
  free(header);
  free(fmt);
  free(data);
  return 0;
}

void decode() {
  char file_name[MAX_FILE_NAME_LEN];
  if (get_file_name_from_user(file_name) != 1) {
    return;
  }

  FILE* fp = fopen(file_name, "rb");
  if (!fp) {
    fprintf(stderr, "error reading the file.\n");
    return;
  }

  WAVHeader* header = getParsedHeader(fp);
  WAVFmtSubChunk* fmt = getParsedFMT(fp);
  print_wav_metadata(fp, fmt);
  WAVDataSubChunk* data = getDataChunk(fp);

  unsigned char extracted_binary_data[SECRET_MESSAGE_LEN * 8];
  size_t max_bits = SECRET_MESSAGE_LEN * 8;
  if (!extract_lsb_message(data->pcm_data, data->data_size, extracted_binary_data, max_bits)) {
    fprintf(stderr, "failed to extract message from WAV.\n");
    fclose(fp);
    free(header);
    free(fmt);
    free(data);
    return;
  }

  uint32_t message_len = 0;
  for (int i = 0; i < 32; ++i) {
    message_len = (message_len << 1) | extracted_binary_data[i];
  }

  if (message_len > SECRET_MESSAGE_LEN) {
    fprintf(stderr, "extracted message length too large.\n");
    fclose(fp);
    free(header);
    free(fmt);
    free(data);
    return;
  }

  char extracted_message[SECRET_MESSAGE_LEN];
  binary_to_string(extracted_binary_data + 32, message_len * 8, extracted_message);
  printf("extracted Message: %s\n", extracted_message);

  fclose(fp);
  free(header);
  free(fmt);
  free(data);
}