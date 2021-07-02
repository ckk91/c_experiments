#ifndef READER_H
#define READER_H
#include <stdio.h>
#include "types.h"


char* read_string_from_input(FILE *fstream);

value* read_symbol(char* str, size_t* pos);
value* read_list(char* str, size_t* pos);
value* read_expr(char* str, size_t* pos);
value* read_num(char* str, size_t* pos);


#endif // !H_READER
