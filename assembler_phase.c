#include "assembler_phase.h"

/* TODO: Add documentation */
int assembler_phase(char** files_list, int files_count) {
    int i, j;
    has_errors = FALSE;
    LinkedCommandList_t actions_names_list = create_action_names_list();
    char *memory_array[MEMORY_SIZE];
    LinkedList_t data_memory_list = create_linked_list();
    Table_t extern_memory_table = create_table();
    LabelsLinkedList_t symbol_table = create_linked_labels_list();

    for (i = 1; i < files_count; i++) { /* TODO: rewrite this */

        printf("DEBUG: Running assembler on %s\n", files_list[i]); /* TODO: delete this */

        run_assembler_phase_1(files_list[i], actions_names_list, &data_memory_list, &symbol_table, memory_array);

        printf("DEBUG: Symbol table after phase 1\n"); /* TODO: delete this */
        print_labels_list(symbol_table); /* TODO: delete this */

        printf("DEBUG: Data memory table after phase 1\n"); /* TODO: delete this */
        print_list(data_memory_list); /* TODO: delete this */

        printf("DEBUG: Memory array after phase 1\n"); /* TODO: delete this */
        for (j = 0; !(StringsEqual(memory_array[j], "\0")); j++) { /* TODO: delete this */
            printf("%d\t%s\n", j + FIRST_AVAILABLE_ADDRESS, memory_array[j]); /* TODO: delete this */
        }


        /* TODO: Understand if phase 2 should happen even if phase 1 has errors and handle accordingly */
        run_assembler_phase_2(files_list[i], actions_names_list, &data_memory_list, &extern_memory_table, &symbol_table, memory_array); /* TODO: decide if to separate to two loops */

        printf("DEBUG: Symbol table after phase 2\n"); /* TODO: delete this */
        print_labels_list(symbol_table); /* TODO: delete this */

        printf("DEBUG: Data memory table after phase 2\n"); /* TODO: delete this */
        print_list(data_memory_list); /* TODO: delete this */

        printf("DEBUG: Memory array after phase 2\n"); /* TODO: delete this */
        for (j = 0; !(StringsEqual(memory_array[j], "\0")); j++) { /* TODO: delete this */
            printf("%d\t%s\n", j + FIRST_AVAILABLE_ADDRESS, memory_array[j]); /* TODO: delete this */
        }

        /* TODO: If any errors - delete all created files */

        /* if not errors - create files! */
        create_files(files_list[i], memory_array, &symbol_table, &extern_memory_table);
    }

    return 0;
    print_assembler_phase();
    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_1(char* file_name, LinkedCommandList_t action_names_list, LinkedList_t *data_memory_list, LabelsLinkedList_t *symbol_table, char *memory_array[]) {
    int ic = 0, dc = 0, l, i; /* Step 1 */
    int label_definition_flag = FALSE; /* TODO: rename this */
    char *line, *command;
    char *relevant_line_bit; /* TODO: rename this is needed */
    /*char *memory_array[MEMORY_SIZE];*/
    /*LinkedList_t split_by_label, data_memory_list, split_by_space;*/
    LinkedList_t split_by_label, split_by_space;
    FILE *source_file;
    FILE *dest_file;
    /*LabelsLinkedList_t symbol_table;*/

    printf("Running phase 1 of assembler on %s!\n", file_name); /* TODO: delete this */

    line_count = 0;
    *data_memory_list = create_linked_list();
    *symbol_table = create_linked_labels_list();
    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);
    source_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), READ);

    for (i = 0; i < MEMORY_SIZE; i++) {
        memory_array[i] = copy_string(DEFAULT_EMPTY_WORD);
    }

    while (ReadLine(source_file, line) != EOF) {  /* TODO: rewrite this */ /* Step 2 */

        /*printf("DEBUG: Handling line [%s]\n", line); *//* TODO: delete this */

        line_count ++;

        if (is_not(is_valid_line(line))) {
            continue;
        }

        line = clean_multiple_whitespaces(line);
        split_by_label = split_string(line, ':');

        if (get_list_length(split_by_label) > 2) {
            /* TODO: Not necessarily true, .string "::::" is a legit line! */
            handle_error("Invalid usage of ':'"); /* TODO: rewrite error */
        }

        relevant_line_bit = get_stripped_string(get_node_value(get_tail(split_by_label)));
        split_by_space = split_string(relevant_line_bit, SPACE);

        if (starts_with_label(split_by_label)) { /* Step 3 */
            label_definition_flag = TRUE; /* Step 4 */
        }

        if (is_data_storage(relevant_line_bit)) { /* Step 5 */
            if (is(label_definition_flag)) { /* Step 6 */
                add_label(*symbol_table, split_by_label, DATA_TYPE, dc);
            }
            /* Step 7 */
            if (is(starts_with(relevant_line_bit, DATA_PREFIX))) {
                dc += handle_data_type(relevant_line_bit, *data_memory_list);
            } else {
                dc += handle_string_type(relevant_line_bit, *data_memory_list);
            }
        } else if (is_extern_or_entry(relevant_line_bit)) { /* Step 8 */
            if (is_extern(relevant_line_bit)) { /* Step 9 */
                /* TODO: Throw warning if label */
                add_label(*symbol_table, split_by_space, EXTERN_TYPE, EXTERN_DEFAULT_VALUE);
            }
        } else {
            if(is(label_definition_flag)) { /* Step 11 */
                add_label(*symbol_table, split_by_label, CODE_TYPE, ic);
            }

            command = get_node_value(get_head(split_by_space));
            /*if(search_command_list(action_names_list, command) == NULL) {  *//* Step 12 *//*
                *//* TODO: ERROR HANDLING - illegal command! *//*
                return -1;
            }*/ /* TODO: Delete this */
            /* Do step 12 + 13 */

            /*memory_array[ic] = copy_string(DEFAULT_EMPTY_WORD);*/

            l = handle_first_word(search_command_list(action_names_list, command), relevant_line_bit, memory_array[ic]);
            /*printf("DEBUG: Memory slot is: %s\n", memory_array[ic]); *//* TODO: delete this *//*
            printf("--------------\n"); *//* TODO: delete this */
            /* TODO: Handle this mess of l and calculate words thingie */
            ic += calculate_words_for_line(search_command_list(action_names_list, command), relevant_line_bit); /* Step 14 */
            /*ic += l;*/ /* Step 14 */
        }

        label_definition_flag = FALSE;
    }

    fclose(source_file);
    /*return 1;*/ /* TODO: delete this */
    if (is(has_errors)) { /* Step 16 */
        printf("ERROR: Found errors in file, stopping assembler\n");
        /*return -1;*/ /* TODO: Uncomment this*/
    }

    dest_file = fopen(concatenate_strings(file_name, OBJECT_FILE_SUFFIX), WRITE);
    fprintf(dest_file, "%d %d\n", ic, dc);
    fclose(dest_file);

    /* TODO: Add documentation */
    update_symbol_table(*symbol_table, ic); /* Step 17 */

    ic = add_data_symbols_to_memory(*data_memory_list, ic, memory_array);

    memory_array[ic] = "\0";

    /*printf("Phase 1 ended, printing symbol table:\n"); *//* TODO: delete this *//*
    print_labels_list(symbol_table); *//* TODO: delete this *//*
    printf("Printing memory list:\n"); *//* TODO: delete this *//*
    print_list(data_memory_list); *//* TODO: delete this *//*
    printf("Printing memory array:\n"); *//* TODO: delete this *//*
    for (i = 0; i <= ic; i++) { *//* TODO: delete this *//*
        printf("%d\t%s\n", i + FIRST_AVAILABLE_ADDRESS, memory_array[i]); *//* TODO: delete this *//*
    } *//* TODO: delete this */

    return has_errors;
}

/* TODO: Add documentation */
int run_assembler_phase_2(char* file_name, LinkedCommandList_t action_names_list, Table_t *data_memory_list, LinkedList_t *extern_memory_table, LabelsLinkedList_t *symbol_table, char *memory_array[]) {
    int ic = 0, l = 0; /* Step 1 */
    char *line, *command;
    char *relevant_line_bit; /* TODO: rename this is needed */
    FILE *source_file;
    LinkedList_t split_by_label, split_by_space;

    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);
    source_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), READ);
    line_count = 0;

    printf("Running phase 2 of assembler on %s!\n", file_name); /* TODO: delete this */

    while (ReadLine(source_file, line) != EOF) {  /* TODO: rewrite this */ /* Step 2 */
        line_count ++;

        if (is_not(is_valid_line(line))) {
            continue;
        }


        line = clean_multiple_whitespaces(line);
        split_by_label = split_string(line, ':');
        relevant_line_bit = get_stripped_string(line);

        if (is(starts_with_label(split_by_label))) { /* Step 3 */
            /* TODO: ERROR HANDLING - Ensure not entry!!! */
            relevant_line_bit = get_stripped_string(get_node_value(get_tail(split_by_label)));
        }

        if (is(is_data_storage(relevant_line_bit)) || is(is_extern(relevant_line_bit))) { /* Step 4 */
            continue;
        }

        if (is(is_entry(relevant_line_bit))) { /* Step 5 */
            /* TODO: ERROR HANDLING - Ensure there aren't too many stuff */
            /* TODO: WARNING HANDLING - in case of label */
            mark_label_as_entry(*symbol_table, get_node_value(get_tail(split_string(relevant_line_bit, SPACE)))); /* Step 6 */
        }
        else /* Step 7+8 */
        {
            split_by_space = split_string(relevant_line_bit, SPACE);
            command = get_node_value(get_head(split_by_space));
            l = handle_all_but_first_words(search_command_list(action_names_list, command), relevant_line_bit, extern_memory_table, symbol_table, memory_array, ic); /* Step 7 */
            ic += l; /* Step 8 */
        }
    }

    fclose(source_file);

    if (is(has_errors)) { /* Step 10 */
        printf("ERROR: Found errors in file, stopping assembler\n");
        return -1;
    }

    /*create_files();*/

    return 0;
}

/* TODO: Add documentation */
int create_files(char* file_name, char *memory_array[], LabelsLinkedList_t *symbol_table, Table_t *external_memory_table) {
    write_object_file(file_name, memory_array);
    create_externals_file(file_name, *external_memory_table);
    create_entries_file(file_name, *symbol_table);
    return 0;
}
