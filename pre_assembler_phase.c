#include "pre_assembler_phase.h"

/* TODO: Add documentation */
int pre_assembler(char** files_list) {
    int i;

    for (i = 0; i < strlen((const char *) files_list); i++) { /* TODO: rewrite this */
        run_pre_assembler_on_file(files_list[i]);
    }

    return 0;
}

/* TODO: Add documentation */
int run_pre_assembler_on_file(char* file_name) {
    char *line = ""; /* TODO: Maybe initialize line better */
    FILE *source_file, *dest_file;

    source_file = fopen(strcat(file_name, INPUT_SUFFIX), READ); /* TODO: add suffix to file_name */
    dest_file = fopen(strcat(file_name, INPUT_SUFFIX), WRITE); /* TODO: add suffix to file_name */

    line = get_next_line(source_file, line);
    while (line[strlen(line) - 1] != EOF) {
        line = get_next_line(source_file, line);
        if (is_start_of_macro(line))
            add_macro(source_file, line);
        else
            write_line_to_expanded_file(dest_file, line);
    }

    fclose(source_file);
    fclose(dest_file);

    return 0;
}

/* TODO: Add documentation */
void write_line_to_expanded_file(FILE *dest_file, char* line) {
    /* TODO: should go through all words in the line, use split and loop it */
    if (is_an_existing_macro(line))
        write_existing_macro(line, dest_file);
    else
        write_line_to_file(dest_file, line); /* TODO: Not line, more like "chunk" */
}
