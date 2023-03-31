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
    char *line;
    FILE *source_file, *dest_file;
    Table_t macro_table;

    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);

    source_file = fopen(concatenate_strings(file_name, INPUT_SUFFIX), READ);
    dest_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), WRITE);

    macro_table = create_table();

    while (ReadLine(source_file, line) != EOF) {  /* TODO: rewrite this */
        line = clean_multiple_whitespaces(line);
        if (is_start_of_macro_definition(line))
            add_macro(source_file, line, macro_table);
        else
            write_line_to_expanded_file(dest_file, line, macro_table);
        /*line = get_next_line_stripped(source_file, line);*/
    }

    fclose(source_file);
    fclose(dest_file);

    return 0;
}

/* TODO: Add documentation */
void write_line_to_expanded_file(FILE *dest_file, char* line, Table_t macro_table) {
    /* TODO: should go through all words in the line, use split and loop it */
    LinkedList_t line_split;
    Node_t current_word;

    line_split = split_string(line, SPACE);
    current_word = get_head(line_split);

    while(current_word != NULL) {
        /* TODO: Maybe combine those two functions to one */
        if (get_node_value(current_word) != get_node_value(get_head(line_split)))
            fputc(SPACE, dest_file);
        if (is_an_existing_macro(get_node_value(current_word), macro_table))
            write_existing_macro(get_node_value(current_word), dest_file, macro_table);
        else
            write_line_to_file(dest_file, get_node_value(current_word)); /* TODO: Not line, more like "chunk" */
        current_word = get_next_node(current_word);
    }
    write_line_to_file(dest_file, "\n");
}
