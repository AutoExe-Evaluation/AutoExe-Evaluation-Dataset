#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int func(int *result, int size);

int* parse_nested_parens(const char *paren_string, int *size) {
    int *result = malloc(100 * sizeof(int)); // Assuming a maximum of 100 groups
    *size = 0;
    
    char *token;
    char *string_copy = strdup(paren_string);
    
    token = strtok(string_copy, " ");
    while (token != NULL) {
        if (strlen(token) == 0) {
            token = strtok(NULL, " ");
            continue;
        }

        int depth = 0;
        int max_depth = 0;
        for (int i = 0; token[i] != '\0'; i++) {
            char c = token[i];
            if (c == '(') {
                depth++;
                if (depth > max_depth) {
                    max_depth = depth;
                }
            } else {
                depth--;
            }
        }

        result[(*size)++] = max_depth;
        token = strtok(NULL, " ");
    }

    free(string_copy);
    
    if (!func(result, *size)) {
        // Handle the assertion failure if necessary
    }

    return result;
}