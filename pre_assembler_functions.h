#ifndef PRE_ASSEMBLER_FUNCTIONS_H
#define PRE_ASSEMBLER_FUNCTIONS_H

#include <stdio.h>
#include "general_functions.h"

void print_pre_assembler_phase(void); /* TODO: delete this */
int is_start_of_macro(char* line); /* TODO: Add documentation */ /* TODO: Change name, use "macro definition" somehow */
void add_macro(FILE *file, char* line); /* TODO: Add documentation */
int is_an_existing_macro(char* line); /* TODO: Add documentation */
int is_legal_macro_name(char* name);/* TODO: Add documentation */
void write_existing_macro(char* macro, FILE *file); /* TODO: delete this */ /* If not */ /* TODO: Add documentation */

#endif
