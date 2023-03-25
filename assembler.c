#include "assembler.h"

Allocator_t global_allocator;

int main(void) {
    global_allocator = create_allocator();

    printf("This is the main assembler!\n");
    /*pre_assembler();*/
    assembler_phase();

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
    char *file_name;
    char *line;
    Table_t t;
    LinkedList_t list;
    Node_t node;
    FILE *file;
    int i;

    printf("This is a test\n");

    printf("These are our strings!\n");
    printf("First: %s, second: %s, third: %s\n", str, str2, str3);

    str3 = copy_string(str);
    str2 = get_string_without_whitespaces(str2);
    printf("First: %s, second: %s, third: %s\n", str, str2, str3);

    t = create_table();

    printf("Searching for %s in t: %s\n", str, get_value(t, str));

    add_to_table_if_not_exists(t, str, str2);
    add_to_table_if_not_exists(t, str2, str);
    add_to_table_if_not_exists(t, str2, str);

    printf("Searching for %s in t: %s\n", str, get_value(t, str));
    printf("Searching for %s in t: %s\n", str2, get_value(t, str2));

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

    printf("Starting file testing!\n");
    file_name = concatenate_strings(luna, SUFFIX);
    printf("File name is %s\n", file_name);
    file = fopen(file_name, "r");
    printf("Opened file\n");
    line = get_next_line(file, line);
    printf("-----reading file-----\n");
    while (line[strlen(line) - 1] != EOF) {
        line = get_next_line(file, line);
        printf("%s", line);
    }
    printf("-----end of file------\n");
    fclose(file);

    free_all_and_allocator();
}
