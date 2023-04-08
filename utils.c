#include "utils.h"
#include "stdio.h"


/* TODO: Add documentation */
char* copy_string(char* str) {
    char* copied_str = (char*)allocate(sizeof(char)*(strlen(str)+1));
    strcpy(copied_str, str);
    return copied_str;
}

/* TODO: Add documentation */
char* copy_substring(char* str, int start, int end) {
    char* copied_str = (char*)allocate(sizeof(char)*(end - start + 1));
    int i;
    for (i = 0; i < end - start; ++i) {
        copied_str[i] = str[start + i];
    }
    copied_str[i] = END_OF_STRING;
    return copied_str;
}

/* TODO: Add documentation */
char* concatenate_strings(char* first, char* second) {
    int i, len, first_len, second_len;
    char* concatenated_str;

    first_len = strlen(first);
    second_len = strlen(second);
    len = first_len + second_len;

    concatenated_str = (char*) allocate(sizeof(char) * (len + 1));

    for (i = 0; i < first_len; i++) {
        concatenated_str[i] = first[i];
    }

    for (i = 0; i < second_len; i++) {
        concatenated_str[i+first_len] = second[i];
    }

    concatenated_str[len]=END_OF_STRING;

    return concatenated_str;
}

/* TODO: Add documentation */
char* append_char_to_string(char* str, int c) {
    char *new_str;
    int i;
    new_str = (char*)allocate(sizeof(char) * (strlen(str) + 2));
    memset(new_str, '0', sizeof(char) * (strlen(str) + 2));
    for (i = 0; i < strlen(str) ; i++) {
        new_str[i] = str[i];
    }
    new_str[i++] = c + 0;
    new_str[i] = END_OF_STRING;
    return new_str;
}
