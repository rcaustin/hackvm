#include "specification.h"


/* Hack ASM Signals */
#define ASM_SIG_QUIT  "QUIT"
#define ASM_SIG_PRNTA "PRINT_A"
#define ASM_SIG_PRNTD "PRINT_D"
#define ASM_SIG_PRNTM "PRINT_M"


void translate_asm(char** source, WORD* buffer, long line_count);
WORD parse_a_instr(char* line);
WORD parse_c_instr(char* line);
