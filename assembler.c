#include "assembler.h"

Allocator_t global_allocator;
int has_errors, line_count;

int main(int argc, char *argv[]) {

    global_allocator = create_allocator();

    pre_assembler(argv, argc);
    assembler_phase(argv, argc);

    free_all_and_allocator();
    return 0;
}