#include "pre_assembler_phase.h"

/*  The function goes through the files_array array (using a for loop)
    and runs the pre-assembler phase on each of those files. */
void pre_assembler(char** files_array, int files_count) {
    int i;

    for (i = 1; i < files_count; i++) {
        printf("INFO: Running pre-assembler phase on %s%s!\n",files_array[i], INPUT_SUFFIX); /* TODO: delete this */
        run_pre_assembler_on_file(files_array[i]);
        free_all(); /* Frees redundant memory that was allocated during this for loop iteration */
    }
}

/*  Gets a file name.
    Ensures a file with .as suffix exists (and if not, returns -1 and notifies of error).
    Go through all lines of the file and for each, checks if it's a macro definition.
    Saves all defined macros in a table.
    We assume that all macros are defined properly and that there are no errors in the file during this step.
    Returns 0 if all ended well and -1 if something went wrong.
 */
int run_pre_assembler_on_file(char* file_name) {
    char *line;  /* String to store the current line of the file we're reading */
    FILE *source_file, *dest_file;  /* The source and destination files */
    Table_t macro_table;  /* The table to contain all defined macros */

    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);

    source_file = fopen(concatenate_strings(file_name, INPUT_SUFFIX), READ);

    if (source_file == NULL) {
        printf("ERROR: File %s%s doesn't exist! Skipping it...\n", file_name, INPUT_SUFFIX);
        return -1;
    }

    dest_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), WRITE);

    macro_table = create_table();

    printf("INFO: Running pre-assemble on %s%s!\n",file_name, INPUT_SUFFIX); /* TODO: delete this */

    while (ReadLine(source_file, line) != EOF) {
        line = get_clean_and_stripped_string(line);
        if (is_start_of_macro_definition(line))
            add_macro(source_file, line, macro_table);
        else
            write_line_to_expanded_file(dest_file, line, macro_table);
    }

    fclose(source_file);
    fclose(dest_file);

    return 0;
}

/*  Gets a destination file, a line and a macro table.
    Splits the line (by space) to words
    Checks for each of if it's a macro defined earlier in the file
        If so, adds the value of it to the destination file.
        If not, adds the word itself to the destination file.
*/
void write_line_to_expanded_file(FILE *dest_file, char* line, Table_t macro_table) {
    char *current_word, *first_word;  /* The word we're currently evaluating and the first word of the line */
    LinkedList_t line_split;  /* Linked list of the words of the given line */
    Node_t current_node;  /* Our current location in the linked list */

    line_split = split_string(line, SPACE);
    first_word = GetHeadValue(line_split);
    current_node = get_head(line_split);

    while(current_node != NULL) {
        current_word = get_node_value(current_node);
        if (StringsNotEqual(current_word, first_word)) /* Adds a space between all words */
            fputc(SPACE, dest_file);
        if (is_an_existing_macro(current_word, macro_table))
            write_existing_macro_to_file(current_word, dest_file, macro_table);
        else
            write_string_to_file(dest_file, current_word);
        current_node = get_next_node(current_node);
    }

    write_string_to_file(dest_file, "\n"); /* Ensures \n between each line */
}
