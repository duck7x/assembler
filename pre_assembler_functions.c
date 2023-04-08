#include "pre_assembler_functions.h"

/*  The function checks if the given line is a beginning of a macro definition
    using starts_with from general_functions */
int is_start_of_macro_definition(char* line) {
    if (starts_with(line, MACRO_DEFINITION_PREFIX))
        return TRUE;
    return FALSE;
}

/*  The function checks if the given line is an ending of a macro definition
    using starts_with from general_functions */
int is_end_of_macro_definition(char* line) {
    if (starts_with(line, MACRO_DEFINITION_SUFFIX)) {
        return TRUE;
    }
    return FALSE;
}

/*  We assume the line is cleaned! */
/*  The function goes through the file from the given line where the beginning mcr is until reaching endmcr
    And adds everything in between to the macro table under the macro name */
void add_macro(FILE *file, char* line, Table_t mcr_table) {
    char* mcr_name;
    LinkedList_t line_split;
    LinkedList_t mcr_content;

    /*line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);*/
    line_split = split_string(clean_multiple_whitespaces(line), SPACE);
    mcr_name = get_node_value(get_next_node(get_head(line_split)));
    /* TODO: Ensure legal macro name and handle error if not */
    mcr_content = create_linked_list();

    ReadLine(file, line);
    /* TODO: might need to support one liners */
    while (is_not(is_end_of_macro_definition(line))) {
        /* Add to current macro */
        add_to_list(create_node(concatenate_strings(line, "\n")), mcr_content);
        ReadLine(file, line);
    }

    /* Add to macro table */
    add_to_table_if_not_exists(mcr_table, mcr_name, get_list_as_string(mcr_content));
}

/* TODO: Add documentation */
int is_an_existing_macro(char* mcr_name, Table_t macro_table) {
    if (get_value_from_table(macro_table, mcr_name) == NULL)
        return FALSE;
    return TRUE;
}

/* TODO: Add documentation */
void write_existing_macro(char* macro, FILE *file, Table_t macro_table) {
    write_line_to_file(file, get_value_from_table(macro_table, macro)); /* TODO: Not line, more like "chunk" */
}

/* TODO: Write this */
/* TODO: Add documentation */
int is_legal_macro_name(char* name) {
    return 0;
}