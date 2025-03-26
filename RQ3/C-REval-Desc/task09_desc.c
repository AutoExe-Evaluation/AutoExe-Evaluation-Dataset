#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(char **result, int count);

char** all_prefixes(const char* string, int* count) {
    int length = strlen(string);
    char** result = (char**)malloc(length * sizeof(char*));
    *count = 0;

    for (int i = 0; i < length; i++) {
        result[i] = (char*)malloc((i + 2) * sizeof(char));
        strncpy(result[i], string, i + 1);
        result[i][i + 1] = '\0';
        (*count)++;
    }

    func(result, *count);
    return result;
}