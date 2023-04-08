#include "assembler.h"

Allocator_t global_allocator; /* Global variable used to allocate memory throughout the program */
int has_errors, line_count; /* Global variables for handling errors */

/*  Main assembler program, gets a list of files from the command line and runs assembler on each of them.
    Using pre_assembler and assembler_phase modules, each given file is checked for errors and if none is found,
    all related files (.am, .ob, .ext and .ent) will be created based on the file.
    The program assumes there are no errors in the macro definitions and during the pre-assembler phase. */
int main(int argc, char *argv[]) {

    global_allocator = create_allocator();

    pre_assembler(argv, argc);
    assembler_phase(argv, argc);

    free_all_and_allocator(); /* Ensures all allocated memory is freed at the end of the program */

    return 0;
}