#include "specification.h"


WORD* read_binary_file(char* path, long* buffer_size);
char** read_text_file(char* path, long* buffer_size);

int write_binary_file(char* path, WORD* buffer, long elem_count);
