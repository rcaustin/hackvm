#include "specification.h"

#include <stdio.h>


void log_error(char* errstr);
void log_warn(char* warnstr);
void log_info(char* infostr);

void fatal_error(char* errstr);

void print_word(WORD word, size_t block_size);
