#include "assembler_phase_functions.h"

void print_assembler_phase(void) {
    printf("This is the assembler phase (printed by assembler phase functions)\n");
}

/* TODO: Add documentation */
int starts_with_label(char *line) {
    LinkedList_t split_line = split_string(line, ':');
    if (get_list_length(split_line) > 1)
        return TRUE;
    return FALSE;
}

/* TODO: Add documentation */
int is_data_storage(char *line){
    if (starts_with(line, DATA_PREFIX) || starts_with(line, STRING_PREFIX))  /* TODO: Maybe improve this */
        return TRUE;
    return FALSE;
}

/* TODO: write this */
/* TODO: Add documentation */
int add_label(int dc) {
    return TRUE;
}

/* TODO: Add documentation */
int is_extern_or_entry(char *line) {
    if (starts_with(line, EXTERN_PREFIX) || starts_with(line, ENTRY_PREFIX))   /* TODO: Maybe improve this */
        return TRUE;
    return FALSE;
}

/* TODO: Add documentation */
int is_extern(char *line) {
    if (starts_with(line, EXTERN_PREFIX))   /* TODO: Maybe improve this */
        return TRUE;
    return FALSE;
}
