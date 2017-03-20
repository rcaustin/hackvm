#include "specification.h"
#include "logging.h"
#include "fileio.h"

#include <stdio.h>
#include <stdlib.h>

WORD D_REGISTER  = 0;
WORD A_REGISTER  = 0;
WORD PC_REGISTER = 0;

WORD RAM[MEMSIZE] = {};
WORD ROM[MEMSIZE] = {};


void load_program(char* path, long* program_size);
void execute_instruction(WORD instruction);

int main(int argc, char* argv[]) {

  if (argc != 2)
    fatal_error("INVALID NUMBER OF ARGUMENTS");

  long program_size = -1;
  load_program(argv[1], &program_size);
  for (;;) {
    execute_instruction(ROM[PC_REGISTER]);
  }

  return 0;
}

void load_program(char* path, long* program_size) {

  WORD* binary_file = read_binary_file(path, program_size);
  *program_size /= sizeof(WORD);
  printf("PROGRAM_SIZE = %ld INSTRUCTIONS\n", *program_size);

  for (size_t i = 0; i < *program_size; i++)
    ROM[i] = binary_file[i];
  free(binary_file);
}

void execute_instruction(WORD instruction) {

  /* Signals */
  switch(instruction) {
  case SIG_QUIT:
    exit(1);
    break;
  case SIG_PRNTA:
    printf("%hu\n", A_REGISTER);
    break;
  case SIG_PRNTD:
    printf("%hu\n", D_REGISTER);
    break;
  case SIG_PRNTM:
    printf("%hu\n", RAM[A_REGISTER]);
    break;
  default:
    break;
  }

  if ((instruction & INST_C) == INST_C) {
    /* C-INSTRUCTION */
    // printf("C-INSTRUCTION:  ");
    WORD result = 0;

    /* Computation */
    switch(instruction & COMP_MASK) {
    case COMP_ZERO:
      // printf("COMP_ZERO ");
      result += 0;
      break;
    case COMP_POS1:
      // printf("COMP_POS1 ");
      result += 1;
      break;
    case COMP_NEG1:
      // printf("COMP_NEG1 ");
      result -= 1;
      break;
    case COMP_D:
      // printf("COMP_D    ");
      result = D_REGISTER;
      break;
    case COMP_A:
      // printf("COMP_A    ");
      result = A_REGISTER;
      break;
    case COMP_CMPD:
      // printf("COMP_CMPD ");
      result = ~D_REGISTER;
      break;
    case COMP_CMPA:
      // printf("COMP_CMPA ");
      result = ~A_REGISTER;
      break;
    case COMP_NEGD:
      // printf("COMP_NEGD ");
      result = D_REGISTER ^ SIGN_MASK;
      break;
    case COMP_NEGA:
      // printf("COMP_NEGA ");
      result = A_REGISTER ^ SIGN_MASK;
      break;
    case COMP_INCD:
      // printf("COMP_INCD ");
      result = D_REGISTER + 1;
      break;
    case COMP_INCA:
      // printf("COMP_INCA ");
      result = A_REGISTER + 1;
      break;
    case COMP_DECD:
      // printf("COMP_DECD ");
      result = D_REGISTER - 1;
      break;
    case COMP_DECA:
      // printf("COMP_DECA ");
      result = A_REGISTER - 1;
      break;
    case COMP_DPA:
      // printf("COMP_DPA  ");
      result = D_REGISTER + A_REGISTER;
      break;
    case COMP_DMA:
      // printf("COMP_DMA  ");
      result = D_REGISTER - A_REGISTER;
      break;
    case COMP_AMD:
      // printf("COMP_AMD  ");
      result = A_REGISTER - D_REGISTER;
      break;
    case COMP_DAA:
      // printf("COMP_DAA  ");
      result = D_REGISTER & A_REGISTER;
      break;
    case COMP_DOA:
      // printf("COMP_DOA  ");
      result = D_REGISTER | A_REGISTER;
      break;
    case COMP_M:
      result = RAM[A_REGISTER];
      break;
    case COMP_CMPM:
      result = ~RAM[A_REGISTER];
      break;
    case COMP_NEGM:
      result = RAM[A_REGISTER] ^ SIGN_MASK;
      break;
    case COMP_INCM:
      result = RAM[A_REGISTER] + 1;
      break;
    case COMP_DECM:
      result = RAM[A_REGISTER] - 1;
      break;
    case COMP_DPM:
      result = D_REGISTER + RAM[A_REGISTER];
      break;
    case COMP_DMM:
      result = D_REGISTER - RAM[A_REGISTER];
      break;
    case COMP_MMD:
      result = RAM[A_REGISTER] - D_REGISTER;
      break;
    case COMP_DAM:
      result = D_REGISTER & RAM[A_REGISTER];
      break;
    case COMP_DOM:
      result = D_REGISTER | RAM[A_REGISTER];
    default:
      log_error("INVALID COMPUTATION INSTRUCTION");
      break;
    }

    /* Destination */
    switch(instruction & DEST_MASK) {
    case DEST_NUL:
      // printf("DEST_NUL ");
      break;
    case DEST_M:
      // printf("DEST_M   ");
      RAM[A_REGISTER] = result;
      break;
    case DEST_D:
      // printf("DEST_D   ");
      D_REGISTER = result;
      break;
    case DEST_MD:
      // printf("DEST_MD  ");
      RAM[A_REGISTER] = result;
      D_REGISTER = result;
      break;
    case DEST_A:
      // printf("DEST_A   ");
      A_REGISTER = result;
      break;
    case DEST_AM:
      // printf("DEST_AM  ");
      RAM[A_REGISTER] = result;
      A_REGISTER = result;
      break;
    case DEST_AD:
      // printf("DEST_AD  ");
      A_REGISTER = result;
      D_REGISTER = result;
      break;
    case DEST_AMD:
      // printf("DEST_AMD ");
      D_REGISTER = result;
      RAM[A_REGISTER] = result;
      A_REGISTER = result;
      break;
    default:
      log_error("INVALID DESTINATION INSTRUCTION");
      break;
    }

    /* Jump */
    switch(instruction & JUMP_MASK) {
    case JUMP_NUL:
      // printf("JUMP_NUL\n");
      ++PC_REGISTER;
      break;
    case JUMP_JGT:
      // printf("JUMP_JGT\n");
      if (result > SIGN_MASK)
        PC_REGISTER = A_REGISTER;
      break;
    case JUMP_JEQ:
      // printf("JUMP_JEQ\n");
      if (result == SIGN_MASK)
        PC_REGISTER = A_REGISTER;
      break;
    case JUMP_JGE:
      // printf("JUMP_JGE\n");
      if (result >= SIGN_MASK)
        PC_REGISTER = A_REGISTER;
      break;
    case JUMP_JLT:
      // printf("JUMP_JLT\n");
      if (result < SIGN_MASK)
        PC_REGISTER = A_REGISTER;
      break;
    case JUMP_JNE:
      // printf("JUMP_JNE\n");
      if (result != SIGN_MASK)
        PC_REGISTER = A_REGISTER;
      break;
    case JUMP_JLE:
      // printf("JUMP_JLE\n");
      if (result <= SIGN_MASK)
        PC_REGISTER = A_REGISTER;
      break;
    case JUMP_JMP:
      // printf("JUMP_JMP\n");
      PC_REGISTER = A_REGISTER;
      break;
    default:
      log_error("INVALID JUMP INSTRUCTION");
      break;
    }
  } else {
    /* A-INSTRUCTION */
    // printf("A-INSTRUCTION:  SET A_REGISTER TO %hu\n", instruction);
    A_REGISTER = instruction;
    ++PC_REGISTER;
  }
}
