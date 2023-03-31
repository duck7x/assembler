#include "assembler.h"

Allocator_t global_allocator;

int main(void) {
    /* TODO: Change file list to linked list */
    /* TODO: Get file list from input */
    char *file_list[1] = {"test2"}; /* TODO: delete this */
    /*char *file_list[2] = {"test", "test2"};*/ /* TODO: delete this */
    /*char *file_list[10] = {"tests/test_1", "tests/test_2", "tests/test_3", "tests/test_4", "tests/test_5", "tests/test_6", "tests/test_7", "tests/test_8", "tests/test_9", "tests/test_10"}; *//* TODO: delete this */
    global_allocator = create_allocator();

    printf("This is the main assembler!\n");  /*TODO: delete this*/
    pre_assembler(file_list);
    assembler_phase(file_list);

    free_all_and_allocator();
    return 0;

    printf("-----------Testing-----------\n");  /* TODO: delete this */
    testing();  /* TODO: delete this*/
    printf("---------Done testing--------\n");  /* TODO: delete this */
    return 0;
}

/* TODO: delete this */
void testing(void) {
    char str[10] = "Timon";
    char *str2 = "L u       n        a     ";
    char *str3 = NULL;
    char *str4 = "Timon/Luna/Small/Cute";
    char *str5 = "  T i m   o   n           ";
    char *str6 = "Timmy";
    char *luna = "luna";
    char *line;
    Table_t t;
    LinkedList_t list;
    Node_t node;
    FILE *file;

    line = (char *)allocate(sizeof(char) * MAX_LINE_LENGTH);
    printf("This is a test\n");

    printf("These are our strings!\n");
    printf("First: %s, second: %s, third: %s\n", str, str2, str3);

    str3 = copy_string(str);
    str2 = get_string_without_whitespaces(str2);
    printf("First: %s, second: %s, third: %s\n", str, str2, str3);

    t = create_table();

    printf("Searching for %s in t: %s\n", str, get_value_from_table(t, str));

    add_to_table_if_not_exists(t, str, str2);
    add_to_table_if_not_exists(t, str2, str);
    add_to_table_if_not_exists(t, str2, str);

    printf("Searching for %s in t: %s\n", str, get_value_from_table(t, str));
    printf("Searching for %s in t: %s\n", str2, get_value_from_table(t, str2));

    printf("First / in %s is %d\n", str4, get_index_till_delimiter(str4, '/'));

    printf("Checking is %s starts with %s: %d\n", str4, str, starts_with(str4, str));
    printf("Checking is %s starts with %s: %d\n", str4, str2, starts_with(str4, str2));
    printf("Checking is %s starts with %s: %d\n", str2, str, starts_with(str2, str));

    str3 = copy_substring(str4, 11, 16);
    printf("Third is %s\n", str3);
    str3 = copy_substring(str4, 0, 0);
    printf("Third is %s\n", str3);

    printf("Five is [%s]\n", str5);
    str5 = get_stripped_string(str5);
    printf("Five is [%s]\n", str5);

    list = create_linked_list();
    node = create_node(str);
    print_list(list);
    add_to_list(node, list);
    node = create_node(str2);
    print_list(list);
    add_to_list(node, list);
    print_list(list);

    printf("Splitting [%s]!\n", str4);
    list = split_string(str4, '/');
    print_list(list);

    printf("Sixth string is %s\n", str6);
    str6 = append_char_to_string(str6, '?');
    printf("Now sixth string is %s\n", str6);

    file = fopen(concatenate_strings(luna, SUFFIX), "r");
    /*line = get_next_line(file, line);*/
    printf("-----reading file-----\n");
    while (ReadLine(file, line) != EOF) {
        printf("%s\n", line);
        /*line = get_next_line(file, line);*/
    }
    printf("-----end of file------\n");
    fclose(file);

    file = fopen(concatenate_strings("pumba", SUFFIX), "r");
    /*line = get_next_line(file, line);*/
    printf("-----before cleaning file-----\n");
    while (ReadLine(file, line) != EOF) {
        printf("%s\n", line);
        /*line = get_next_line(file, line);*/
    }
    printf("-----end of file------\n");
    fclose(file);

    file = fopen(concatenate_strings("pumba", SUFFIX), "r");
    /*line = get_next_line_stripped(file, line);*/
    printf("-----after cleaning file-----\n");
    while (ReadLine(file, line) != EOF) {
        printf("%s\n", clean_multiple_whitespaces(line));
        /*line = get_next_line_stripped(file, line);*/
    }
    printf("-----end of file------\n");
    fclose(file);

    free_all_and_allocator();
}
