#include "assembler.h"

#include <stdio.h>
#include <stdlib.h>

#include "logging.h"
#include "fileio.h"


int main(int argc, char* argv[]) {

  if (argc < 2 || argc > 3)
    fatal_error("INVALID NUMBER OF ARGUMENTS");

  long line_count  = 0;
  char** source = read_text_file(argv[1], &line_count);
  WORD* instructions = calloc(line_count, sizeof(WORD));

  for (signed long i = 0; i < line_count; i++)
    instructions[i] = parse_hack_asm(source[i]);

  /* TODO: WRITE INSTRUCTIONS TO A.OUT */
  int success = 0;
  char* output = (argc == 3) ? argv[2] : "asm/a.out";
  success = write_binary_file(output, instructions, line_count);

  if (success > 0)
    printf("ASM Output Written to %s;  %d Instructions Written\n", output, success);
  else
    log_warn("NO INSTRUCTIONS WRITTEN TO ASM OUT");

  return 0;
}

WORD parse_hack_asm(char* line) {

  WORD instruction = 0;

  if (line[0] == '@') {
    /* A-INSTRUCTION */
    long long unsigned int num = 0;

    if (sscanf(line, "@%lld", &num) != 1) {
      log_warn(line);
      fatal_error("INVALID HASM INSTRUCTION");
    }
    if (num > MAXADDR) {
      log_warn(line);
      fatal_error("INVALID MEMORY ADDRESS");
    }
    instruction = (WORD)num;
  } else {
    /* TODO: C-INSTRUCTION */

  }

  return instruction;
}
