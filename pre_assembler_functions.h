#ifndef PRE_ASSEMBLER_FUNCTIONS_H
#define PRE_ASSEMBLER_FUNCTIONS_H

#include <stdio.h>
#include "general_functions.h"

#define MACRO_DEFINITION_PREFIX "mcr " /* TODO: Add documentation */
#define MACRO_DEFINITION_SUFFIX "endmcr" /* TODO: Add documentation */

void print_pre_assembler_phase(void); /* TODO: delete this */

/* Checks if a given line is a macro definition. Gets an array representing a line, returns TRUE if it's a macro definition and FALSE otherwise*/
int is_start_of_macro_definition(char* line);

/* Checks if a given line is an en of a macro definition. Gets an array representing a line, returns TRUE if it's an end of a macro definition and FALSE otherwise*/
int is_end_of_macro_definition(char* line);

/* Gets a file and the current line, adds the macro that is defined in that line to the known macros in mcr_table */
void add_macro(FILE *file, char* line, Table_t mcr_table);
int is_an_existing_macro(char* line); /* TODO: Add documentation */
int is_legal_macro_name(char* name);/* TODO: Add documentation */
void write_existing_macro(char* macro, FILE *file); /* TODO: delete this */ /* If not */ /* TODO: Add documentation */

#endif
