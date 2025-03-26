#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** separate_paren_groups(const char* paren_string, int* returnSize) {
    char** result = (char**)malloc(sizeof(char*) * strlen(paren_string));
    char current_string[100];
    int current_depth = 0;
    int j = 0;
    int k = 0;

    for (int i = 0; paren_string[i] != '\0'; i++) {
        char c = paren_string[i];
        if (c == '(') {
            current_depth++;
            current_string[j++] = c;
        } else if (c == ')') {
            current_depth--;
            current_string[j++] = c;

            if (current_depth == 0) {
                current_string[j] = '\0';
                result[*returnSize] = (char*)malloc(strlen(current_string) + 1);
                strcpy(result[*returnSize], current_string);
                (*returnSize)++;
                j = 0;
            }
        }
    }

    return result;
}

// Assuming the definition of func is available elsewhere
// assert(func(result)); // POST condition demonstration