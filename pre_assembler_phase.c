#include "pre_assembler_phase.h"

/* TODO: Add documentation */
int pre_assembler(char** files_list) {
    int i;

    for (i = 0; i < 1; i++) { /* TODO: rewrite this */
        run_pre_assembler_on_file(files_list[i]);
    }

    return 0;
}

/* TODO: Add documentation */
int run_pre_assembler_on_file(char* file_name) {
    char *line = ""; /* TODO: Maybe initialize line better */
    FILE *source_file, *dest_file;
    Table_t macro_table;

    printf("Running assembler on %s\n", file_name);
    source_file = fopen(concatenate_strings(file_name, INPUT_SUFFIX), READ);
    dest_file = fopen(concatenate_strings(file_name, OUTPUT_SUFFIX), WRITE);

    macro_table = create_table();

    line = get_next_line_stripped(source_file, line);
    while (line[strlen(line) - 1] != EOF) {  /* TODO: rewrite this */
        if (is_start_of_macro_definition(line))
            add_macro(source_file, line, macro_table);
        else
            write_line_to_expanded_file(dest_file, line);
        line = get_next_line_stripped(source_file, line);
    }

    printf("No longer in while, last line is %s\n", line);

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
