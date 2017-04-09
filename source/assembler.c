#include "assembler.h"

#include <stdio.h>

#include "logging.h"
#include "fileio.h"


int main(int argc, char* argv[]) {

  if (argc != 2)
    fatal_error("INVALID NUMBER OF ARGUMENTS");

  signed long line_count  = 0;
  char** hasm_source = read_file_by_line(argv[1], &line_count);

  for (long i = 0; i < line_count; i++)
    if (hasm_source[i])
      printf("LINE %li:  %s\n", line_count, hasm_source[i]);

  return 0;
}
