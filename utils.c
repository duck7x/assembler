#include "utils.h"


/*
    Gets a string and returns a copy of it using strcpy.
*/
char* copy_string(char* str) {
    char* copied_str = (char*)allocate((int)(sizeof(char)*(strlen(str)+1)));
    strcpy(copied_str, str);
    return copied_str;
}

/*
    Gets a string, a start index and an end index.
    Copies the substring from the start index till the end index of the given string.
    This is done using a for loop.
*/
char* copy_substring(const char* str, int start, int end) {
    char* copied_str = (char*)allocate((int)(sizeof(char)*(end - start + 1)));
    int i;

    for (i = 0; i < end - start; ++i) {
        copied_str[i] = str[start + i];
    }

    copied_str[i] = END_OF_STRING;
    return copied_str;
}

/*
    Gets two strings (first and second).
    Using two for loops, concatenates them so that the first
    given string would appear first, then the second given string will appear.
*/
char* concatenate_strings(char* first, char* second) {
    int i, len, first_len, second_len;
    char* concatenated_str;

    first_len = (int)strlen(first);
    second_len = (int)strlen(second);
    len = first_len + second_len;

    /* the new string that would hold both strings */
    concatenated_str = (char*) allocate((int)sizeof(char) * (len + 1));

    /* Adding the first string to the start of the new string */
    for (i = 0; i < first_len; i++) {
        concatenated_str[i] = first[i];
    }

    /* Adding the second string to the first one*/
    for (i = 0; i < second_len; i++) {
        concatenated_str[i+first_len] = second[i];
    }

    concatenated_str[len]=END_OF_STRING;

    return concatenated_str;
}
