#include "fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logging.h"

#define MAX_LINE_COUNT  32
#define MAX_LINE_LENGTH 128


WORD* read_binary_file(char* path, long* buffer_size) {

  WORD* source = NULL;
  FILE* file   = fopen(path, "rb");

  if (file != NULL) {
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

char** read_file_by_line(char* path, long* buffer_size) {

  char** lines = malloc(MAX_LINE_COUNT * MAX_LINE_LENGTH * sizeof(char));
  FILE*  file  = file = fopen(path, "r");
  int    i     = 0;

  if (file != NULL) {
    while (fgets(lines[i], MAX_LINE_LENGTH, file)) {
      //lines[i][strlen(lines[i]) - 1] = '\0';
      ++i;
    }
  }
  fclose(file);
  *buffer_size = i;

  return lines;
}
