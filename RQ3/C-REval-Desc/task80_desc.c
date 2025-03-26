#include <stdbool.h>
#include <string.h>

bool func(bool result);

bool cycpattern_check(const char* a, const char* b) {
    int l = strlen(b);
    char pat[2 * l + 1];
    strcpy(pat, b);
    strcat(pat, b);
    bool result = false;
    
    for (int i = 0; i <= strlen(a) - l; i++) {
        for (int j = 0; j <= l; j++) {
            if (strncmp(a + i, pat + j, l) == 0) {
                result = true;
            }
        }
    }

    return func(result);
}