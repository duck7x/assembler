#include "assembler_phase.h"

/* TODO: Add documentation */
int assembler_phase(char** files_list) {
    int i;

    for (i = 0; i < 2; i++) { /* TODO: rewrite this */
        run_assembler_phase_1(files_list[i]);
        run_assembler_phase_2(files_list[i]); /* TODO: decide if to separate to two loops */
    }

    return 0;
    print_assembler_phase();
    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_1(char* file_name) {
    int ic = 0, dc = 0; /* Step 1 */
    int err = 0; /* TODO: Handle errors with linked list */
    int label = FALSE; /* TODO: rename this */
    char *line;
    FILE *source_file, *dest_file;

    printf("Running phase 1 of assembler on %s!\n", file_name); /* TODO: delete this */

    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);
    source_file = fopen(concatenate_strings(file_name, POST_PRE_ASSEMBLER_SUFFIX), READ);
    dest_file = fopen(concatenate_strings(file_name, ".temp"), WRITE);

    while (ReadLine(source_file, line) != EOF) {  /* TODO: rewrite this */ /* Step 2 */
        line = clean_multiple_whitespaces(line);
        if (starts_with_label(line)) { /* Step 3 */
            label = TRUE; /* Step 4 */
        }
        if (is_data_storage(line)) { /* Step 5 */
            if (is(label)) { /* Step 6 */
                add_label(dc);
            }
            /* Do step 7 */
        } else if (is_extern_or_entry(line)) { /* Step 8 */
            if (is_extern(line)) { /* Step 9 */
                /* Do step 9 */
            }
        } else {
            if(is(label)) { /* Step 11 */
                /* Do step 11 */
            }
            /* Do step 12 */
            /* Do step 13 */
            /* Do step 14 */
        }
    }

    err = line[0]; /* TODO: delete this */

    if (err != 0) { /* TODO: WRITE THIS AND HANDLE ERRORS PROPERLY */ /* Step 16 */
        printf("ERROR: Found errors in file, stopping assembler");
        return -1;
    }

    /* TODO: STEP 17 */

    return 0;
}

/* TODO: Add documentation */
int run_assembler_phase_2(char* file_name) {
    printf("Running phase 2 of assembler on %s!\n", file_name); /* TODO: delete this */
    return 0;
}
