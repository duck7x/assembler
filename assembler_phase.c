#include "assembler_phase.h"

/* TODO: Add documentation */
int assembler_phase(char** files_list) {
    int i;

    for (i = 0; i < 1; i++) { /* TODO: rewrite this */
        run_assembler_phase_1(files_list[i]);
        /* TODO: Understand if phase 2 should happen even if phase 1 has errors and handle accordingly */
        run_assembler_phase_2(files_list[i]); /* TODO: decide if to separate to two loops */
    }

    return 0;
    print_assembler_phase();
    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_1(char* file_name) {
    int ic = 100, dc = 0, l = 0; /* Step 1 */
    int label_definition_flag = FALSE; /* TODO: rename this */
    char *line;
    char *relevant_line_bit; /* TODO: rename this is needed */
    LinkedList_t split_by_label, error_list, warning_list, memory_list;
    FILE *source_file, *dest_file;
    LabelsLinkedList_t symbol_table;

    printf("Running phase 1 of assembler on %s!\n", file_name); /* TODO: delete this */

    error_list = create_linked_list();
    warning_list = create_linked_list();
    memory_list = create_linked_list();
    symbol_table = create_linked_labels_list();
    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);
    source_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), READ);
    dest_file = fopen(concatenate_strings(file_name, ".temp"), WRITE);

    while (ReadLine(source_file, line) != EOF) {  /* TODO: rewrite this */ /* Step 2 */

        line = clean_multiple_whitespaces(line);
        /* TODO: Skip line if empty or comment */
        split_by_label = split_string(line, ':');

        if (get_list_length(split_by_label) > 2) {
            /* TODO: Not necessarily true, .string "::::" is a legit line! */
            handle_error(error_list, "Invalid usage of ':'"); /* TODO: rewrite error */
        }

        relevant_line_bit = get_stripped_string(get_node_value(get_tail(split_by_label)));

        if (starts_with_label(split_by_label)) { /* Step 3 */
            label_definition_flag = TRUE; /* Step 4 */
        }

        if (is_data_storage(relevant_line_bit)) { /* Step 5 */
            if (is(label_definition_flag)) { /* Step 6 */
                add_label(symbol_table, split_by_label, DATA_TYPE, dc);
            }
            /* Do step 7 */
            if (is(starts_with(relevant_line_bit, DATA_PREFIX))) {
                dc += handle_data_type(relevant_line_bit, memory_list);
            } else {
                dc += handle_string_type(relevant_line_bit, memory_list);
            }
        } else if (is_extern_or_entry(relevant_line_bit)) { /* Step 8 */
            if (is_extern(relevant_line_bit)) { /* Step 9 */
                /* TODO: Throw warning if label */
                add_label(symbol_table, split_by_label, EXTERN_TYPE, EXTERN_DEFAULT_VALUE);
            }
        } else {
            if(is(label_definition_flag)) { /* Step 11 */
                add_label(symbol_table, split_by_label, CODE_TYPE, ic);
            }
            /* Do step 12 */
            /* Do step 13 */
            ic += l; /* Step 14 */
        }

        label_definition_flag = FALSE;
        ic += 1; /* TODO: delete this */
    }

    fclose(source_file);
    fclose(dest_file);

    if (get_list_length(error_list) != 0) { /* Step 16 */
        printf("ERROR: Found errors in file, stopping assembler\n");
        return -1;
    }

    /* TODO: Rename this */
    /* TODO: Add documentation */
    update_symbol_table(symbol_table, ic); /* Step 17 */

    printf("Phase 1 ended, printing symbol table:\n"); /* TODO: delete this */
    print_labels_list(symbol_table); /* TODO: delete this */
    printf("Printing memory list:\n"); /* TODO: delete this */
    print_list(memory_list); /* TODO: delete this */

    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_2(char* file_name) {
    printf("Running phase 2 of assembler on %s!\n", file_name); /* TODO: delete this */
    return 0;
}
