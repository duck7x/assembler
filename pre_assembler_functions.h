#ifndef PRE_ASSEMBLER_FUNCTIONS_H /* Prevents recursive includes */
#define PRE_ASSEMBLER_FUNCTIONS_H

#include "general_functions.h"

#define MACRO_DEFINITION_PREFIX "mcr " /* A prefix that indicates a beginning of a macro definition */
#define MACRO_DEFINITION_SUFFIX "endmcr" /* A prefix that indicates the end of a macro definition */

/*  Gets a string representing a line.
    Checks if that string is a beginning of a macro definition
    INPUT:  line is a string representing a line of the file. (should be cleaned and trimmed)
    OUTPUT: TRUE if the string is a beginning of a macro definition
            FALSE if the string is not a beginning of a macro definition
*/
int is_start_of_macro_definition(char* line);

/*  Gets a string representing a line.
    Checks if that string is the end of a macro definition
    INPUT:  line is a string representing a line of the file. (should be cleaned and trimmed)
    OUTPUT: TRUE if the string is an end of a macro definition
            FALSE if the string is not an end of a macro definition
*/
int is_end_of_macro_definition(char* line);

/*  Gets a file, the current line and the current macro table (all macros that were defined earlier in the file)
    The current line should be a beginning of a macro definition.
    Adds the macro defined in that line (and the following lines) to the given macro table,
    after ensuring the macro name is valid.
    INPUT:  file is the file we're currently reading.
            line is a string representing the current line. (should be cleaned and trimmed)
            mcr_table is a table that contains all earlier defined macros.
    OUTPUT: The function doesn't return anything.
*/
void add_macro(FILE *file, char* line, Table_t mcr_table);

/*  Gets a macro name and a macro table, checks if the macro has already been defined according to the table.
    INPUT:  mcr_name is the macro we're looking for.
            macro_table is the table of macros to look through.
    OUTPUT: TRUE if the macro is defined in the given table
            FALSE if the macro is not defined in the given table
*/
int is_an_existing_macro(char* mcr_name, Table_t macro_table);

/*  Gets a macro name and writes its contents to a given file,
    according to a given macro table.
    INPUT:  macro is the desired macro's name.
            file is the destination file.
            macro_table is the defined table of macros.
    OUTPUT: The function doesn't return anything.
*/
void write_existing_macro_to_file(char* macro, FILE *file, Table_t macro_table);

/*  Gets a string representing a macro name and ensures it's a legal macro name.
    INPUT:  name - a string representing a macro name.
    OUTPUT: TRUE if the given name is a legal macro name,
            FALSE if the given name isn't a legal macro name.
*/
int is_legal_macro_name(char* name);

#endif
