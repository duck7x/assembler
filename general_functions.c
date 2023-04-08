#include "general_functions.h"

/* TODO: Add documentation */
void handle_error(char *error_message) {
    has_errors = TRUE;
    printf("ERROR: %s on line %d\n", error_message, line_count);
}

/* TODO: Add documentation */
void handle_warning(char *warning_message) {
    printf("WARNING: %s on line %d\n", warning_message, line_count);
}

/* TODO: Add documentation */
int starts_with(char *str, char *prefix) {
    if (strncmp(prefix, str, strlen(prefix)) == 0)
        return TRUE;
    return FALSE;
}

/* TODO: Add documentation */
int get_index_till_delimiter(char* str, char delimiter) {
    char* delimiter_address = strchr(str, delimiter);
    if (delimiter_address) {
        return (int)(delimiter_address - str);
    }
    return -1;
}

/* TODO: Add documentation */
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

/* TODO: Ensure that works! */
/* TODO: Add documentation */
char* get_clean_and_stripped_string(char* str) {
    int i;
    int cleaned_str_index = 0;
    int following_space = TRUE;

    i = 0;
    while (str[i] != END_OF_STRING) {
        if (isSpace(str[i])) {
            if (!is(following_space)) {
                following_space = TRUE;
                str[cleaned_str_index] = SPACE;
                cleaned_str_index++;
            }
        } else {
            following_space = FALSE;
            str[cleaned_str_index] = str[i];
            cleaned_str_index++;
        }
        i++;
    }

    if (isSpace(str[cleaned_str_index - 1]))
        str[cleaned_str_index - 1] = END_OF_STRING;
    else
        str[cleaned_str_index] = END_OF_STRING;

    return str;
}

/* TODO: Add documentation */
/* Replaces all spaces (including tabs!) with a single space! */
char* clean_multiple_whitespaces(char* str) {
    int i;
    /*char* cleaned_str;*/
    int cleaned_str_index = 0;
    int following_space = FALSE;

    /*cleaned_str = copy_string(str);*/
    i = 0;
    while (str[i] != END_OF_STRING) {
        if (isSpace(str[i])) {
            if (!is(following_space)) {
                following_space = TRUE;
                str[cleaned_str_index] = SPACE;
                cleaned_str_index++;
            }
        } else {
            following_space = FALSE;
            str[cleaned_str_index] = str[i];
            cleaned_str_index++;
        }
        i++;
    }

    str[cleaned_str_index] = END_OF_STRING;

    return str;

}

/* TODO: Add documentation */
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

/* TODO: Add documentation */
char* get_stripped_string(char* str) {
    int first_char = 0, last_char = strlen(str);

    if (strlen(str) == 0) {
        return "\0";
    }

    while(isSpace(str[first_char]) && first_char < last_char)
        first_char ++;

    while(isSpace(str[last_char - 1]) && last_char > 0)
        last_char --;

    return copy_substring(str, first_char, last_char);
}

/* TODO: Add documentation */
void write_string_to_file(FILE* file, char* string) {
    fputs(string, file);
}
