#include "general_functions.h"

int starts_with(char *str, char *prefix) {
    char *temp;

    if (strlen(prefix) > strlen(str))
        return FALSE;

    temp = copy_string(str);
    temp[strlen(prefix)] = '\0';
    printf("prefix len is %d and temp len is %d\n", strlen(prefix), strlen(temp));

    /*memcpy(temp, str, strlen(prefix));*/

    /*temp[strlen(prefix)] = '\0';*/
    if (strcmp(prefix, temp) == 0)
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

char* clean_string(char* str) {
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
