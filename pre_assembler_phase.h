#ifndef PRE_ASSEMBLER_PHASE_H
#define PRE_ASSEMBLER_PHASE_H

#include <stdio.h>
#include "pre_assembler_functions.h"

int pre_assembler(char** files_list); /* Gets list of files, runs pre-assembler on each of them */
int run_pre_assembler_on_file(char* file_name); /* Runs pre-assembler phase on a given file by file name */
void write_line_to_expanded_file(FILE *dest_file, char* line, Table_t macro_table); /* Gets a line, writes expanded version of it to the given file */

#endif
