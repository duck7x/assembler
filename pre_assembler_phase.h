#ifndef PRE_ASSEMBLER_PHASE_H /* Prevents recursive includes */
#define PRE_ASSEMBLER_PHASE_H

#include "pre_assembler_functions.h"

/*  Gets a list of files and that list's length.
    For each of those files, runs the pre-assembler phase on the filename with .as suffix.
    Which means, for each file, creates an .am file based on the .as file, with all macros expanded.

    INPUT:  files_array is an array of string containing filenames (without suffix).
            files_count is the amount of files given.
    OUTPUT: This function doesn't return anything.
*/
void pre_assembler(char** files_array, int files_count);

/*  Gets a file name and runs the pre-assembler phase on it.
    The function will create a file with .am suffix which contains the extended macros file.

    INPUT:  file_name is the name of the file. The function will run the pre-assembler phase on file_name.as
    OUTPUT: 0 if no errors were encountered and -1 if any errors occurred.
 */
int run_pre_assembler_on_file(char* file_name);

/*  Gets a file, a line and a macro_table.
    Adds the extended version of that line to the given file, based on the macro_table.

    INPUT:  dest_file is the .am file to write to.
            line is the current line (from the .as file).
            macro_table is a table containing all macros defined so far in the .as file.
    OUTPUT: This function doesn't return anything.
*/
void write_line_to_expanded_file(FILE *dest_file, char* line, Table_t macro_table);

#endif
