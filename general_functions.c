#include "general_functions.h"

int starts_with(char *str, char *prefix) {
    if (strncmp(prefix, str, strlen(prefix)) == 0)
        return TRUE;
    return FALSE;
}

int get_index_till_delimiter(char* str, char delimiter) {
    char* delimiter_address = strchr(str, delimiter);
    if (delimiter_address) {
        return (int)(delimiter_address - str);
    }
    return -1;
}

LinkedList_t split_string(char* str, char delimiter) {
    LinkedList_t list;
    int curr_index;
    char* temp;
    Node_t node;

    list = create_linked_list();
    curr_index = get_index_till_delimiter(str, delimiter);
    temp = copy_string(str);

    while (curr_index > -1) {
        node = create_node(copy_substring(temp, 0, curr_index));
        add_to_list(node, list);
        temp = copy_substring(temp, curr_index + 1, strlen(temp));
        curr_index = get_index_till_delimiter(temp, delimiter);
    }
    node = create_node(temp);
    add_to_list(node, list);
    return list;
}

char* get_string_without_whitespaces(char* str) {
    int i;
    int str_len = strlen(str);
    char* cleaned_str;
    int cleaned_str_index = 0;

    cleaned_str = copy_string(str);

    for (i=0; i <= str_len; i++) {
        if (!isSpace(str[i])) {
            cleaned_str[cleaned_str_index] = str[i];
            cleaned_str_index++;
        }
    }

    return cleaned_str;
}
