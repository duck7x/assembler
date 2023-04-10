#include "assembler_phase.h"

/*  Gets an array of files, and the amount of files in that array.
    This function assumes that the pre-assembler phase has already been done for each of those files.
    Using a for loop, the function goes through the files in the list and runs the first and second assembler phase for it.
    If both phases went well with no errors (as indicated by the has_errors global variable),
    Creates all required files using create_files function.
    If there were any errors during the first or second phase of the assembler,
    All created files (including the one created by the pre-assembler) will be deleted.
    In such case, a CRITICAL message will be printed.
*/
int assembler_phase(char** files_list, int files_count) {
    int i;
    char *memory_array[MEMORY_SIZE], *current_file;  /* Represents the code image of the assembler */
    LinkedCommandList_t actions_names_list = create_action_names_list();  /* Contains the allowed assembly commands */
    LabelsLinkedList_t symbol_table = create_linked_labels_list();  /* Will contain all the labels in the code */
    LinkedList_t data_memory_list = create_linked_list();  /* Represents the data image of the assembler  */
    Table_t extern_memory_table = create_table();  /* Will contain all the external labels usage in the code */

    has_errors = FALSE;

    for (i = 1; i < files_count; i++) {

        has_errors = FALSE;  /* Ensures that errors in previous files will not affect the following ones */

        current_file = files_list[i];
        run_assembler_phase_1(current_file, actions_names_list, &data_memory_list, &symbol_table, memory_array);
        run_assembler_phase_2(current_file, actions_names_list, &extern_memory_table, &symbol_table, memory_array);

        if (is_not(has_errors))  /* Files will be created only if both assembler phase finished with no errors */
            create_files(current_file, memory_array, &symbol_table, &extern_memory_table);
        else {  /* Some files are created during the process. If there has been any errors, those files needs to be deleted */
            printf("CRITICAL: Not creating files for %s due to previous errors\n", current_file);
            delete_created_files(current_file);
            return -1;
        }
    }

    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_1(char* file_name, LinkedCommandList_t action_names_list, LinkedList_t *data_memory_list, LabelsLinkedList_t *symbol_table, char *memory_array[]) {
    int i, ic = 0, dc = 0, label_definition_flag = FALSE;
    char *line, *command;
    char *relevant_line_bit;
    LinkedList_t split_by_label, split_by_space;
    FILE *source_file, *dest_file;

    line_count = 0;
    *data_memory_list = create_linked_list();
    *symbol_table = create_linked_labels_list();
    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);
    source_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), READ);

    if (source_file == NULL) {
        printf("ERROR: File %s%s doesn't exist! Skipping it...\n", file_name, POST_PRE_ASSEMBLER_SUFFIX);
        has_errors = TRUE;
        return -1;
    }

    for (i = 0; i < MEMORY_SIZE; i++) {
        memory_array[i] = copy_string(DEFAULT_EMPTY_WORD);
    }

    while (ReadLine(source_file, line) != EOF) {

        line_count ++;

        if (is_not(is_valid_line(line))) {
            continue;
        }

        line = clean_multiple_whitespaces(line);
        split_by_label = split_string(line, COLON);

        if (get_list_length(split_by_label) > 2) {
            /* TODO: Not necessarily true, .string "::::" is a legit line! */
            handle_error("Invalid usage of ':'"); /* TODO: rewrite error */
        }

        relevant_line_bit = get_stripped_string(GetTailValue(split_by_label));
        split_by_space = split_string(relevant_line_bit, SPACE);

        if (starts_with_label(split_by_label)) {
            label_definition_flag = TRUE;
        }

        if (is_data_storage(relevant_line_bit)) {
            if (is(label_definition_flag)) {
                add_label(*symbol_table, split_by_label, DATA_TYPE, dc);
            }

            if (is(starts_with(relevant_line_bit, DATA_PREFIX))) {
                dc += handle_data_type(relevant_line_bit, *data_memory_list);
            } else {
                dc += handle_string_type(relevant_line_bit, *data_memory_list);
            }

        } else if (is_extern_or_entry(relevant_line_bit)) {
            if (is_extern(relevant_line_bit)) {
                if(is(label_definition_flag)) {
                    handle_warning("Label before extern/entry instruction");
                }
                add_label(*symbol_table, split_by_space, EXTERN_TYPE, EXTERN_DEFAULT_VALUE);
            }
        } else {
            if(is(label_definition_flag)) {
                add_label(*symbol_table, split_by_label, CODE_TYPE, ic);
            }

            command = GetHeadValue(split_by_space);
            if(search_command_list(action_names_list, command) == NULL)
                handle_error("Illegal command");

            handle_first_word(search_command_list(action_names_list, command), relevant_line_bit, memory_array[ic]);
            /* TODO: Handle this mess of l and calculate words thingie */
            ic += calculate_words_for_line(search_command_list(action_names_list, command), relevant_line_bit); /* Step 14 */
        }

        label_definition_flag = FALSE;

    }

    fclose(source_file);

    if (is(has_errors)) {
        printf("ERROR: Found errors in file, stopping assembler phase 1\n");
        return -1;
    }

    dest_file = fopen(concatenate_strings(file_name, OBJECT_FILE_SUFFIX), WRITE);
    fprintf(dest_file, "%d %d\n", ic, dc);
    fclose(dest_file);

    update_symbol_table(*symbol_table, ic);

    ic = add_data_symbols_to_memory(*data_memory_list, ic, memory_array);

    memory_array[ic] = "\0";

    return has_errors;

}

/* TODO: Add documentation */
int run_assembler_phase_2(char* file_name, LinkedCommandList_t action_names_list, Table_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[]) {
    int l, ic = 0;
    char *line, *command, *relevant_line_bit;
    FILE *source_file;
    LinkedList_t split_by_label, split_by_space;

    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);
    source_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), READ);
    line_count = 0;

    if (source_file == NULL) {
        printf("ERROR: File %s%s doesn't exist! Skipping it...\n", file_name, POST_PRE_ASSEMBLER_SUFFIX);
        has_errors = TRUE;
        return -1;
    }

    while (ReadLine(source_file, line) != EOF) {
        line_count ++;

        if (is_not(is_valid_line(line))) {
            continue;
        }

        line = clean_multiple_whitespaces(line);
        split_by_label = split_string(line, COLON);
        relevant_line_bit = get_stripped_string(line);

        if (is(starts_with_label(split_by_label))) {
            /* TODO: ERROR HANDLING - Ensure not entry!!! */
            relevant_line_bit = get_stripped_string(GetTailValue(split_by_label));
        }

        if (is(is_data_storage(relevant_line_bit)) || is(is_extern(relevant_line_bit))) {
            continue;
        }

        if (is(is_entry(relevant_line_bit))) {
            split_by_space = split_string(relevant_line_bit, SPACE);
            if (get_list_length(split_by_space) > 1) {
                handle_error("Too many parameters after .entry instruction");
            }
            mark_label_as_entry(*symbol_table, GetTailValue(split_by_space)); /* Step 6 */
        }

        else {
            split_by_space = split_string(relevant_line_bit, SPACE);
            command = GetHeadValue(split_by_space);
            l = handle_all_but_first_words(search_command_list(action_names_list, command), relevant_line_bit, extern_memory_table, symbol_table, memory_array, ic); /* Step 7 */
            ic += l;
        }
    }

    fclose(source_file);

    return is(has_errors) ? 0 : -1;
}

/*  Gets a file name, a memory array, a symbol table and an externals memory table.
    Generates all relevant files using write_object_file, create_externals_file and create_entries_file function.
*/
void create_files(char* file_name, char *memory_array[], LabelsLinkedList_t *symbol_table, Table_t *external_memory_table) {
    write_object_file(file_name, memory_array);
    create_externals_file(file_name, *external_memory_table);
    create_entries_file(file_name, *symbol_table);
}

/*  Gets a string representing a file name.
    Attempts to remove all files with that name and assembly compiler related suffixes, using the files remove method.
    Suffixes to be deleted are POST_PRE_ASSEMBLER_SUFFIX, OBJECT_FILE_SUFFIX, EXTERNALS_FILE_SUFFIX and ENTRIES_FILE_SUFFIX.
*/
void delete_created_files(char *file_name) {
    remove(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX));
    remove(concatenate_strings(file_name, OBJECT_FILE_SUFFIX));
    remove(concatenate_strings(file_name, EXTERNALS_FILE_SUFFIX));
    remove(concatenate_strings(file_name, ENTRIES_FILE_SUFFIX));
}
