#ifndef PRE_ASSEMBLER_FUNCTIONS_H
#define PRE_ASSEMBLER_FUNCTIONS_H

#include <stdio.h>
#include "general_functions.h"

void print_pre_assembler_phase(void);
int is_start_of_macro(char* line); /* TODO: Change name, use "macro definition" somehow */
void add_macro(FILE *file, char* line);
int is_an_existing_macro(char* line);
int is_legal_macro_name(char* name);
void write_existing_macro(char* macro, FILE *file);

#endif
