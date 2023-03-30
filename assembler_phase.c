#include "assembler_phase.h"

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

int run_assembler_phase_1(char* file_name) {
    printf("Running phase 1 of assembler on %s!\n", file_name); /* TODO: delete this */
    return 0;
}

int run_assembler_phase_2(char* file_name) {
    printf("Running phase 2 of assembler on %s!\n", file_name); /* TODO: delete this */
    return 0;
}
