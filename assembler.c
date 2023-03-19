#include "assembler.h"

int main(void) {
    printf("This is the main assembler!\n");
    pre_assembler();
    assembler_phase();

    printf("-----------Testing-----------\n");  /* TODO: delete this */
    testing();  /* TODO: delete this */
    return 0;
}

/* TODO: delete this */
void testing(void) {
    Allocator_t *allocator;
    printf("This is a test\n");
    allocator = create_allocator();
    free_all_and_allocator(allocator);
}