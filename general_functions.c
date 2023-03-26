#include "general_functions.h"

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

/* TODO: Add documentation */
/* Replaces all spaces (including tabs!) with a single space! */
char* clean_multiple_whitespaces(char* str) {
    int i;
    int str_len = strlen(str);
    char* cleaned_str;
    int cleaned_str_index = 0;
    int following_space = FALSE;

    cleaned_str = copy_string(str);

    for (i = 0; i < str_len; i++) {
        if (isSpace(str[i])) {
            if (!is(following_space)) {
                following_space = TRUE;
                cleaned_str[cleaned_str_index] = SPACE;
                cleaned_str_index++;
            }
        } else {
            following_space = FALSE;
            cleaned_str[cleaned_str_index] = str[i];
            cleaned_str_index++;
        }
    }

    cleaned_str[cleaned_str_index] = '\0';

    return cleaned_str;

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

    while(isSpace(str[first_char]) && first_char < last_char)
        first_char ++;

    while(isSpace(str[last_char - 1]) && last_char > 0)
        last_char --;

    return copy_substring(str, first_char, last_char);
}

/* TODO: Add documentation */
/* TODO: Make this better without allocating so much */
/* TODO: Adding EOF to string is bad, don't do it, it causes ? to be printed */
char* get_next_line(FILE* file, char* line) {
    int c;
    line = copy_substring(line, 0, 0);
    while (((c = getc(file)) != NEWLINE) && (c != EOF)) {
        line = append_char_to_string(line, c);
    }
    line = append_char_to_string(line, c);
    return line;
}

/* TODO: Add documentation */
/* TODO: Make this better without allocating so much */
/* TODO: Adding EOF to string is bad, don't do it, it causes ? to be printed */
char* get_next_line_stripped(FILE* file, char* line) {
    int c;
    line = copy_substring(line, 0, 0);
    while (((c = getc(file)) != NEWLINE) && (c != EOF)) {
        line = append_char_to_string(line, c);
    }
    line = append_char_to_string(line, c);
    return clean_multiple_whitespaces(line);
}

/* TODO: Add documentation */
/* TODO: write this */
void write_line_to_file(FILE* file, char* line) {
    printf("Writing [ %s ] to file! (Not really)\n", line);
}
