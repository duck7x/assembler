#include "general_functions.h"

void print_new_line(void){
    printf("\n");
    printf("(New line printed by general functions)\n");
}

int starts_with(char *str, char *prefix) {
    char *temp;

    memcpy(temp, str, strlen(prefix));
    temp[strlen(prefix)] = '\0';
    return strcmp(prefix, temp);
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
