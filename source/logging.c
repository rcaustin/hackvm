#include "logging.h"

#include <stdlib.h>


void log_error(char* errstr) {

  printf("ERR: %s\n", errstr);
}

void log_warn(char* warnstr) {

  printf("WARN: %s\n", warnstr);
}

void log_info(char* infostr) {

  printf("INFO: %s\n", infostr);
}

void fatal_error(char* errstr) {

  printf("FATAL ERROR\n");
  log_error(errstr);
  exit(1);
}

void print_word(WORD word, size_t block_size) {

  char bits[16] = {};
  for (size_t i = 0; i < 16; ++i) {
    if (word & 1)
      bits[15-i] = '1';
    else
      bits[15-i] = '0';
    word >>= 1;
  }
  for (size_t i = 0; i < 16; ++i) {
    printf("%c", bits[i]);
    if ((i+1) % block_size == 0)
      printf(" ");
  }
  printf("\n");
}
