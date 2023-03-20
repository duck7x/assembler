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
    char str[10] = "Timon";
    char *str2 = "L u       n        a     ";
    char *str3 = NULL;
    Allocator_t allocator;

    printf("This is a test\n");
    allocator = create_allocator();

    printf("These are our strings!\n");
    printf("First: %s, second: %s, third: %s\n", str, str2, str3);

    str3 = copy_string(allocator, str);
    str2 = clean_string(allocator, str2);
    printf("First: %s, second: %s, third: %s\n", str, str2, str3);

    free_all_and_allocator(allocator);
}