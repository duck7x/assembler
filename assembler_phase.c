#include "assembler_phase.h"

/* TODO: Add documentation */
int assembler_phase(char** files_list) {
    int i, has_errors = 0;
    LinkedCommandList_t actions_names_list = create_action_names_list();

    for (i = 2; i < 3; i++) { /* TODO: rewrite this */
        has_errors += run_assembler_phase_1(files_list[i], actions_names_list);
        /* TODO: Understand if phase 2 should happen even if phase 1 has errors and handle accordingly */
        has_errors += run_assembler_phase_2(files_list[i], actions_names_list); /* TODO: decide if to separate to two loops */
        /* if not errors - create files! */
    }

    return 0;
    print_assembler_phase();
    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_1(char* file_name, LinkedCommandList_t action_names_list) {
    int ic = 0, dc = 0, l = 0, count = 0, i, has_errors = FALSE; /* Step 1 */
    int label_definition_flag = FALSE; /* TODO: rename this */
    char *line, *command;
    char *relevant_line_bit; /* TODO: rename this is needed */
    char *memory_array[MEMORY_SIZE];
    LinkedList_t split_by_label, data_memory_list, split_by_space;
    FILE *source_file, *dest_file;
    LabelsLinkedList_t symbol_table;

    printf("Running phase 1 of assembler on %s!\n", file_name); /* TODO: delete this */

    data_memory_list = create_linked_list();
    symbol_table = create_linked_labels_list();
    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);
    source_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), READ);
    dest_file = fopen(concatenate_strings(file_name, ".temp"), WRITE);

    while (ReadLine(source_file, line) != EOF) {  /* TODO: rewrite this */ /* Step 2 */

        printf("DEBUG: Handling line [%s]\n", line); /* TODO: delete this */

        if (is_not(is_valid_line(line)))
            continue;

        count ++;

        line = clean_multiple_whitespaces(line);
        /* TODO: Skip line if empty or comment */
        split_by_label = split_string(line, ':');

        if (get_list_length(split_by_label) > 2) {
            /* TODO: Not necessarily true, .string "::::" is a legit line! */
            handle_error("Invalid usage of ':'", count, &has_errors); /* TODO: rewrite error */
        }

        relevant_line_bit = get_stripped_string(get_node_value(get_tail(split_by_label)));
        split_by_space = split_string(relevant_line_bit, SPACE);

        if (starts_with_label(split_by_label)) { /* Step 3 */
            label_definition_flag = TRUE; /* Step 4 */
        }

        if (is_data_storage(relevant_line_bit)) { /* Step 5 */
            if (is(label_definition_flag)) { /* Step 6 */
                add_label(symbol_table, split_by_label, DATA_TYPE, dc, &has_errors, count);
            }
            /* Step 7 */
            if (is(starts_with(relevant_line_bit, DATA_PREFIX))) {
                dc += handle_data_type(relevant_line_bit, data_memory_list);
            } else {
                dc += handle_string_type(relevant_line_bit, data_memory_list);
            }
        } else if (is_extern_or_entry(relevant_line_bit)) { /* Step 8 */
            if (is_extern(relevant_line_bit)) { /* Step 9 */
                /* TODO: Throw warning if label */
                add_label(symbol_table, split_by_space, EXTERN_TYPE, EXTERN_DEFAULT_VALUE, &has_errors, count);
            }
        } else {
            if(is(label_definition_flag)) { /* Step 11 */
                add_label(symbol_table, split_by_label, CODE_TYPE, ic, &has_errors, count);
            }

            command = get_node_value(get_head(split_by_space));
            /*if(search_command_list(action_names_list, command) == NULL) {  *//* Step 12 *//*
                *//* TODO: ERROR HANDLING - illegal command! *//*
                return -1;
            }*/ /* TODO: Delete this */
            /* Do step 12 + 13 */

            memory_array[ic] = copy_string("00000000000000");

            l = handle_first_word(search_command_list(action_names_list, command), relevant_line_bit, memory_array[ic], count, &has_errors);
            printf("DEBUG: Memory slot is: %s\n", memory_array[ic]); /* TODO: delete this */
            printf("--------------\n"); /* TODO: delete this */
            ic += l; /* Step 14 */
        }

        label_definition_flag = FALSE;
        ic += 1; /* TODO: delete this */
    }

    fclose(source_file);
    fclose(dest_file);
    return 1; /* TODO: delete this */
    if (is(has_errors)) { /* Step 16 */
        printf("ERROR: Found errors in file, stopping assembler\n");
        return -1;
    }

    /* TODO: Rename this */
    /* TODO: Add documentation */
    update_symbol_table(symbol_table, ic); /* Step 17 */

    printf("Phase 1 ended, printing symbol table:\n"); /* TODO: delete this */
    print_labels_list(symbol_table); /* TODO: delete this */
    printf("Printing memory list:\n"); /* TODO: delete this */
    print_list(data_memory_list); /* TODO: delete this */
    printf("Printing memory array:\n"); /* TODO: delete this */
    for (i = 0; i < count; i++) { /* TODO: delete this */
        printf("%d\t%s\n", i + FIRST_AVAILABLE_ADDRESS, memory_array[i]); /* TODO: delete this */
    } /* TODO: delete this */

    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_2(char* file_name, LinkedCommandList_t action_names_list) {
    printf("Running phase 2 of assembler on %s!\n", file_name); /* TODO: delete this */
    return 0;
}
