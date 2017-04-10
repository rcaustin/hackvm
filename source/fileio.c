#include "fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logging.h"

#define MAX_LINE_COUNT  32
#define MAX_LINE_LENGTH 128 * sizeof(char)


WORD* read_binary_file(char* path, long* buffer_size) {

  WORD* source = NULL;
  FILE* file   = fopen(path, "rb");

  if (file) {
    /* Seek to EOF */
    if (fseek(file, 0L, SEEK_END) == 0) {
      /* Store Size of File */
      *buffer_size = ftell(file);
      /* Allocate Buffer of File Size */
      source = malloc(*buffer_size);
      /* Seek to BOF */
      if (fseek(file, 0L, SEEK_SET))
        fatal_error("FAILED TO SEEK TO BOF");
      /* Read File Contents to Buffer */
      fread(source, sizeof(WORD), *buffer_size, file);
      if (ferror(file))
        fatal_error("FAILED TO READ FILE CONTENTS TO BUFFER");
    }
    fclose(file);
  }
  return source;
}

char** read_text_file(char* path, long* buffer_size) {

  FILE*  file  = fopen(path, "r");
  char** lines = (char**) calloc(MAX_LINE_COUNT, sizeof(char*));
  for (int i = 0; i < MAX_LINE_COUNT; i++)
    lines[i] = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
  int i = 0;

  if (file != NULL && lines != NULL) {
    while (fgets(lines[i], MAX_LINE_LENGTH, file) && i < MAX_LINE_COUNT) {
      lines[i][strlen(lines[i])-1] = '\0';
      i++;
    }
  }
  fclose(file);
  *buffer_size = i;

  return lines;
}

int write_binary_file(char* path, WORD* buffer, long elem_count) {

  if (access(path, F_OK) != -1) {
    fatal_error("ASM OUTPUT FILE ALREADY EXISTS");
    return 0;
  }
  else {
    FILE* file = fopen(path, "wb");

    int writes = 0;
    if (file)
      writes = fwrite(buffer, sizeof(WORD), elem_count, file);

    return writes;
  }
}
