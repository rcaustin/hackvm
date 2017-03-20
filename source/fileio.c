#include "fileio.h"

#include <stdio.h>
#include <stdlib.h>

#include "logging.h"


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
