#include "pre_assembler_functions.h"

void print_pre_assembler_phase(void) {
    printf("This is the pre-assembler phase (printed by pre-assembler phase functions)\n");
}

/* TODO: Write this */
/*  The function checks if the given line is a beginning of a macro definition
    using starts_with from general_functions */
int is_start_of_macro_definition(char* line) {
    if (starts_with(line, MACRO_DEFINITION_PREFIX))
        return TRUE;
    return FALSE;
}

/* TODO: Write this */
/*  The function goes through the file from the given line where the beginning mcr is until reaching endmcr
    And adds everything in between to the macro table under the macro name */
void add_macro(FILE *file, char* line, Table_t mcr_table) {
    char* mcr_name;
    LinkedList_t line_split;

    /*line_split = split_string(line,)*/
}

/* TODO: Write this */
/* TODO: Add documentation */
int is_an_existing_macro(char* line) {
    return 0;
}

/* TODO: Write this */
/* TODO: Add documentation */
int is_legal_macro_name(char* name) {
    return 0;
}

/* TODO: Write this */
/* TODO: Add documentation */
void write_existing_macro(char* macro, FILE *file) {
}