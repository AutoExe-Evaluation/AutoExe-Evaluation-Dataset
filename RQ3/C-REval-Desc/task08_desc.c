#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest(char** strings, int size) {
    if (size == 0) {
        return NULL;
    }

    int maxlen = 0;
    for (int i = 0; i < size; i++) {
        int len = strlen(strings[i]);
        if (len > maxlen) {
            maxlen = len;
        }
    }

    for (int i = 0; i < size; i++) {
        if (strlen(strings[i]) == maxlen) {
            return strings[i];
        }
    }

    return NULL;
}