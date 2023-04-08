#include "assembler.h"

Allocator_t global_allocator;
int has_errors, line_count;

int main(int argc, char *argv[]) {
    /* TODO: Change file list to linked list */
    /* TODO: Get file list from input */

    int i;
    global_allocator = create_allocator();

    printf("DEBUG: This is the main assembler!\n");  /*TODO: delete this*/
    pre_assembler(argv, argc);
    assembler_phase(argv, argc);

    free_all_and_allocator();
    return 0;
}