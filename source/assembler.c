#include "assembler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logging.h"
#include "utility.h"
#include "fileio.h"


int main(int argc, char* argv[]) {

  if (argc < 2 || argc > 3)
    fatal_error("INVALID NUMBER OF ARGUMENTS");

  long line_count  = 0;
  char** source = read_text_file(argv[1], &line_count);
  WORD* instructions = calloc(line_count, sizeof(WORD));

  /* Parse ASM and Create Machine Language Instruction Buffer */
  for (signed long i = 0; i < line_count; i++)
    instructions[i] = parse_hack_asm(source[i]);

  /* Write Instructions to .hack Binary File */
  int success = 0;
  char* output = (argc == 3) ? argv[2] : "asm/a.hack";
  success = write_binary_file(output, instructions, line_count);

  if (success > 0)
    printf("ASM OUTPUT WRITTEN TO %s\n%d INSTRUCTIONS WRITTEN\n", output, success);
  else
    log_warn("NO INSTRUCTIONS WRITTEN TO ASM OUT");

  return 0;
}

void translate_asm(char** source, WORD* buffer, long line_count) {

  // CASES:

  // COMMENT:  DO NOTHING
  // // (Two Consecutive Forward Slashes)

  // WHITESPACE:  DO NOTHING
  //    (Spaces, Tabs, or Empty Lines)

  // SYMBOL DECLARATION:  BIND SYMBOL TO ADDRESS; STORE FOLLOWING COMMAND IN ADDRESS
  // Any sequence of Letters, Digits, Underscore, Dot, Dollar Sign, and Colon
  // DOES NOT BEGIN WITH DIGIT

  // CONSTANT:  CHECK SIZE; WRITE/USE CONSTANT
  // Non-Negative Number in Decimal Notation

  // A-INSTRUCTION
  // @ FOLLOWED BY 15-bit MEMORY ADDRESS

  // C-INSTRUCTION
  // COMP
  // DEST=COMP
  // COMP;JUMP
  // DEST=COMP;JUMP
}

WORD parse_a_instr(char* line) {

  long long unsigned int num = 0;

  if (sscanf(line, "@%llu", &num) != 1) {
    log_warn(line);
    fatal_error("INVALID A-INSTRUCTION");
  }
  if (num > MAXADDR) {
    log_warn(line);
    fatal_error("INVALID MEMORY ADDRESS");
  }

  return (WORD)num;
}

WORD parse_c_instr(char* line) {

  WORD dest    = DEST_NUL;
  WORD comp    = C_INST;
  WORD jump    = JUMP_NUL;

  int term = strlen(line);
  int eqls = 0;
  int semi = term;

  for (int i = 0; i < term; i++) {
    if (line[i] == '=') {
      if (eqls == 0)
        eqls = i;
      else
        fatal_error("INVALID C-INSTRUCTION:  MORE THAN 1 '=' FOUND");
    }
    if (line[i] == ';') {
      if (semi == term)
        semi = i;
      else
        fatal_error("INVALID C-INSTRUCTION:  MORE THAN 1 ';' FOUND");
    }
    if (eqls > semi)
      fatal_error("INVALID C-INSTRUCTION:  ';' PRECEDES '='");
  }

  // PARSE DEST
  if (eqls != 0) {
    char dest_str[4];
    substr(line, 0, 3, dest_str);

    if (strstr(dest_str, "A"))
      dest |= DEST_A;
    if (strstr(dest_str, "M"))
      dest |= DEST_M;
    if (strstr(dest_str, "D"))
      dest |= DEST_D;
  }

  // PARSE COMP
  for (int i = eqls; i < semi; i++) {
    char* comp_str = malloc(sizeof(char) * (semi - eqls));
    substr(line, (eqls == 0 ? 0 : eqls + 1), comp_str);

    // TODO: FINISH COMPUTATION SUBSTR
  }

  // PARSE JUMP
  if (semi != term) {
    char jump_str[4];
    substr(line, semi+1, 3, jump_str);

    if (strcmp(jump_str, "JGT"))
      jump = JUMP_JGT;
    if (strcmp(jump_str, "JEQ"))
      jump = JUMP_JEQ;
    if (strcmp(jump_str, "JGE"))
      jump = JUMP_JGE;
    if (strcmp(jump_str, "JLT"))
      jump = JUMP_JLT;
    if (strcmp(jump_str, "JNE"))
      jump = JUMP_JNE;
    if (strcmp(jump_str, "JLE"))
      jump = JUMP_JLE;
    if (strcmp(jump_str, "JMP"))
      jump = JUMP_JMP;
  }

  return dest | comp | jump;
}
