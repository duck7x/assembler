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
/*  The function checks if the given line is a beginning of a macro definition
    using starts_with from general_functions */
int is_end_of_macro_definition(char* line) {
    if (starts_with(line, MACRO_DEFINITION_SUFFIX)) {
        return TRUE;
    }
    return FALSE;
}

/* TODO: Write this */
/*  We assume the line is cleaned! */
/*  The function goes through the file from the given line where the beginning mcr is until reaching endmcr
    And adds everything in between to the macro table under the macro name */
void add_macro(FILE *file, char* line, Table_t mcr_table) {
    char* mcr_name;
    LinkedList_t line_split;
    LinkedList_t mcr_content;

    line_split = split_string(line, SPACE);
    mcr_name = get_node_value(get_next_node(get_head(line_split)));
    line = get_next_line(file, line);
    mcr_content = create_linked_list();

    printf("Adding macro!\n");

    /* TODO: might need to support one liners */
    while (is_not(is_end_of_macro_definition(line))) {
        printf("Adding line [%s] to list\n", line);
        /* Add to current macro */
        add_to_list(create_node(line), mcr_content);
        line = get_next_line(file, line);
    }

    printf("==============\n");
    printf("Macro [%s] is:\n", mcr_name);
    print_list(mcr_content);
    printf("==============\n");

    /* Add to macro table */
    /*add_to_table_if_not_exists(mcr_table, mcr_name, mcr_content);*/ /* TODO: Fix this */
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