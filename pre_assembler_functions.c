#include "pre_assembler_functions.h"

/*  Gets a string representing a line.
    Checking if that string starts with the MACRO_DEFINITION_PREFIX
    If so, returns TRUE.
    Otherwise, returns FALSE.
    The function assumes that the string is already trimmed, so there are no
    trailing whitespace characters at the start of it (this should be taken care of by the code calling the function).
*/
int is_start_of_macro_definition(char* line) {
    if (starts_with(line, MACRO_DEFINITION_PREFIX))
        return TRUE;
    return FALSE;
}

/*  Gets a string representing a line.
    Checking if that string starts with the MACRO_DEFINITION_SUFFIX
    If so, returns TRUE.
    Otherwise, returns FALSE.
    The function assumes that the string is already trimmed, so there are no
    trailing whitespace characters at the start of it (this should be taken care of by the code calling the function).
*/
int is_end_of_macro_definition(char* line) {
    if (starts_with(line, MACRO_DEFINITION_SUFFIX)) {
        return TRUE;
    }
    return FALSE;
}

/*  Gets a string representing the current line, which should be a beginning of a macro definition.
    Ensures the macro name, as defined in that line, is valid.
    If it isn't, the functions stops.
    If it is, the function adds all the following lines, until reaching the end of the macro definition,
    to a linked list.
    Once macro definition has ended, a string is generated from that list and is added to the macro table for future use.
    The function assumes that the string is already trimmed, so there are no
    trailing whitespace characters at the start of it (this should be taken care of by the code calling the function).
*/
void add_macro(FILE *file, char* line, Table_t mcr_table) {
    char *mcr_name, *mcr_string_content;
    LinkedList_t mcr_content;

    mcr_name = get_node_value(get_next_node(get_head(split_string(line, SPACE))));

    if (is_not(is_legal_macro_name(mcr_name))) {
        handle_error("Illegal macro name");
        return;
    }

    mcr_content = create_linked_list();

    ReadLine(file, line);

    while (is_not(is_end_of_macro_definition(line))) {
        add_value_to_list(concatenate_strings(line, "\n"), mcr_content);
        ReadLine(file, line);
    }

    mcr_string_content = get_list_as_string(mcr_content);
    mcr_string_content[strlen(mcr_string_content) - 2] = END_OF_STRING; /* TODO: Ensure this works! */ /* Remove \n at the end of the macro */
    add_to_table_if_not_exists(mcr_table, mcr_name, mcr_string_content);
}

/*  Gets a string representing a macro name and a macro table.
    Using the get_value_from_table function, retrieves the value of that macro, if it's defined.
    If the macro is not defined in the table, NULL will be returned from get_value_from_table,
    and so the function will return FALSE.
    If the value returned is not NULL, this means the macro is indeed defined in the table,
    and so function will return TRUE.
*/
int is_an_existing_macro(char* mcr_name, Table_t macro_table) {
    if (get_value_from_table(macro_table, mcr_name) == NULL)
        return FALSE;
    return TRUE;
}

/*  Gets a string representing a macro name, a table of macros and a destination file.
    Gets the value of that macro from that table, and writes that value to the destination file.
*/
void write_existing_macro_to_file(char* macro, FILE *file, Table_t macro_table) {
    write_string_to_file(file, get_value_from_table(macro_table, macro));
}

/* TODO: Write this */
/* TODO: Add documentation */
int is_legal_macro_name(char* name) {
    return TRUE;
}