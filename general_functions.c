#include "general_functions.h"

/*  This function gets a string, representing an error message.
    The function sets the global variable has_errors to TRUE.
    The function prints an error message to the user,
    containing the given message as well as the line number of the error.
    Printing the line number is done via the line_count global variable.
*/
void handle_error(char *error_message) {
    has_errors = TRUE;
    printf("ERROR: %s on line %d\n", error_message, line_count);
}

/*  This function gets a string, representing a warning message.
    The function prints a warning message to the user,
    containing the given message as well as the line number of the warning.
    Printing the line number is done via the line_count global variable.
*/
void handle_warning(char *warning_message) {
    printf("WARNING: %s on line %d\n", warning_message, line_count);
}

/*  The function gets two strings.
    Using strncmp, checks if the first string starts with the second string.
*/
int starts_with(char *str, char *prefix) {
    if (strncmp(prefix, str, strlen(prefix)) == 0)
        return TRUE;
    return FALSE;
}

/*  Gets a string and a delimiter character.
    Using strchr and pointers arithmetics, calculates the index right
    before the delimiter appears in the string.
    If the delimiter doesn't appear in the string, returns -1.
*/
int get_index_till_delimiter(char* str, char delimiter) {
    char* delimiter_address = strchr(str, delimiter);
    if (delimiter_address) {
        return (int)(delimiter_address - str);
    }
    return -1;
}

/*  Gets a string and a character delimiter.
    Using get_index_till_delimiter, split the string to a linked list
    Which contains the string's sub-words as split by the given delimiter.
    The delimiter will not appear in the list at all.
*/
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
        add_node_to_list(node, list);
        temp = copy_substring(temp, curr_index + 1, strlen(temp));
        curr_index = get_index_till_delimiter(temp, delimiter);
    }
    node = create_node(temp);
    add_node_to_list(node, list);
    return list;
}

/*  Gets a string.
    Cleans it up by removing any trailing whitespaces at the end and start of it
    And combining all consecutive whitespaces to a single space character.
*/
/* TODO: Ensure that works! */
char* get_clean_and_stripped_string(char* str) {
    int i = 0, cleaned_str_index = 0;
    int following_space = TRUE;  /* Handles any trailing whitespaces at the start of the string */

    while (str[i] != END_OF_STRING) {
        if (isSpace(str[i])) {
            if (!is(following_space)) {
                following_space = TRUE;
                str[cleaned_str_index++] = SPACE;
            }
        } else {
            following_space = FALSE;
            str[cleaned_str_index++] = str[i];
        }
        i++;
    }

    if (isSpace(str[cleaned_str_index - 1]))  /* Handles any trailing whitespaces at the end of the string */
        str[cleaned_str_index - 1] = END_OF_STRING;
    else
        str[cleaned_str_index] = END_OF_STRING;

    return str;
}

/*  Gets a string.
    Cleans it up combining all consecutive whitespaces to a single space character.
*/
char* clean_multiple_whitespaces(char* str) {
    int i = 0, cleaned_str_index = 0, following_space = FALSE;

    while (str[i] != END_OF_STRING) {
        if (isSpace(str[i])) {
            if (!is(following_space)) {
                following_space = TRUE;
                str[cleaned_str_index++] = SPACE;
            }
        } else {
            following_space = FALSE;
            str[cleaned_str_index++] = str[i];
        }
        i++;
    }

    str[cleaned_str_index] = END_OF_STRING;

    return str;

}

/*  Gets a string.
    Removes any whitespaces that appear in it.
*/
char* get_string_without_whitespaces(char* str) {
    int i;
    int str_len = strlen(str);
    char* cleaned_str;
    int cleaned_str_index = 0;

    cleaned_str = copy_string(str);

    for (i=0; i <= str_len; i++) {
        if (!isSpace(str[i])) {
            cleaned_str[cleaned_str_index++] = str[i];
        }
    }

    return cleaned_str;
}

/*  Gets a string.
    Cleans it up by removing any trailing whitespaces at the end and start of it.
*/
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

/* Gets a file and a string.
   Add that string to the file using fputs.
   The given file should be in editing mode (write or append).
*/
void write_string_to_file(FILE* file, char* string) {
    fputs(string, file);
}
