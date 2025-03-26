#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* Strongest_Extension(const char* class_name, char* extensions[], int length) {
    char* strong = extensions[0];
    int my_val = 0;

    for (int i = 0; i < strlen(extensions[0]); i++) {
        if (isupper(extensions[0][i])) my_val++;
        if (islower(extensions[0][i])) my_val--;
    }

    for (int i = 1; i < length; i++) {
        int val = 0;
        for (int j = 0; j < strlen(extensions[i]); j++) {
            if (isupper(extensions[i][j])) val++;
            if (islower(extensions[i][j])) val--;
        }
        if (val > my_val) {
            strong = extensions[i];
            my_val = val;
        }
    }

    static char result[256];
    snprintf(result, sizeof(result), "%s.%s", class_name, strong);
    
    // assert(func(result)); // This line is not translatable to C directly and is omitted.

    return result;
}