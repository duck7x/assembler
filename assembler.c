#include "assembler.h"

Allocator_t global_allocator;

int main(int argc, char *argv[]) {
    /* TODO: Change file list to linked list */
    /* TODO: Get file list from input */

    int i;
    global_allocator = create_allocator();

    printf("DEBUG: Got %d arguments!\n", argc); /* TODO: delete this */
    for (i = 0; i < argc; i++) {
        printf("DEBUG: Argument #%d is %s\n", i, argv[i]); /* TODO: delete this */
    }

    printf("This is the main assembler!\n");  /*TODO: delete this*/
    pre_assembler(argv, argc);
    assembler_phase(argv, argc);

    free_all_and_allocator();
    return 0;
}