#include "assembler_phase.h"

/* TODO: Add documentation */
int assembler_phase(char** files_list) {
    int i;

    for (i = 0; i < 1; i++) { /* TODO: rewrite this */
        run_assembler_phase_1(files_list[i]);
        run_assembler_phase_2(files_list[i]); /* TODO: decide if to separate to two loops */
    }

    return 0;
    print_assembler_phase();
    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_1(char* file_name) {
    int ic = 0, dc = 0, l = 0; /* Step 1 */
    int err = 0; /* TODO: Handle errors with linked list */
    int label_definition_flag = FALSE; /* TODO: rename this */
    char *line;
    char *relevant_line_bit; /* TODO: rename this is needed */
    LinkedList_t split_by_label;
    FILE *source_file, *dest_file;
    LabelsLinkedList_t symbol_table;

    printf("Running phase 1 of assembler on %s!\n", file_name); /* TODO: delete this */

    symbol_table = create_linked_labels_list();
    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);
    source_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), READ);
    dest_file = fopen(concatenate_strings(file_name, ".temp"), WRITE);

    while (ReadLine(source_file, line) != EOF) {  /* TODO: rewrite this */ /* Step 2 */
        line = clean_multiple_whitespaces(line);
        split_by_label = split_string(line, ':');
        /* TODO: ERROR HANDLING - if split_string has more than 2 members */
        relevant_line_bit = get_node_value(get_tail(split_by_label));
        if (starts_with_label(split_by_label)) { /* Step 3 */
            label_definition_flag = TRUE; /* Step 4 */
        }
        if (is_data_storage(relevant_line_bit)) { /* Step 5 */
            if (is(label_definition_flag)) { /* Step 6 */
                add_label(symbol_table, split_by_label, DATA_TYPE, dc);
            }
            /* Do step 7 */
            if (is(starts_with(relevant_line_bit, DATA_PREFIX))) {
                handle_data_type(relevant_line_bit);
            } else {
                handle_string_type(relevant_line_bit);
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
    }

    fclose(source_file);
    fclose(dest_file);

/*    err = line[0]; *//* TODO: delete this *//*

    if (err != 0) { *//* TODO: WRITE THIS AND HANDLE ERRORS PROPERLY *//* *//* Step 16 *//*
        printf("ERROR: Found errors in file, stopping assembler\n");
        return -1;
    }*/

    /* TODO: Rename this */
    /* TODO: Add documentation */
    update_symbol_table(symbol_table, ic); /* Step 17 */

    printf("Phase 1 ended, printing symbol table\n"); /* TODO: delete this */
    print_labels_list(symbol_table); /* TODO: delete this */

    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_2(char* file_name) {
    printf("Running phase 2 of assembler on %s!\n", file_name); /* TODO: delete this */
    return 0;
}
