#include <stdio.h>
#include <string.h>
#include <ctype.h>

int func(const char *result);

void file_name_check(const char *file_name) {
    const char *suf[] = {"txt", "exe", "dll"};
    char *lst[2];
    char *file_name_copy = strdup(file_name);
    char *_result = "Yes";
    
    lst[0] = strtok(file_name_copy, ".");
    lst[1] = strtok(NULL, ".");

    if (lst[1] == NULL || lst[0] == NULL || strtok(NULL, ".") != NULL) {
        _result = "No";
    }
    if (lst[1] != NULL && (strcmp(lst[1], suf[0]) != 0 && strcmp(lst[1], suf[1]) != 0 && strcmp(lst[1], suf[2]) != 0)) {
        _result = "No";
    }
    if (strlen(lst[0]) == 0) {
        _result = "No";
    }
    if (!isalpha(lst[0][0])) {
        _result = "No";
    }
    
    int digit_count = 0;
    for (int i = 0; i < strlen(lst[0]); i++) {
        if (isdigit(lst[0][i])) {
            digit_count++;
        }
    }
    if (digit_count > 3) {
        _result = "No";
    }

    assert(func(_result));
    free(file_name_copy);
}