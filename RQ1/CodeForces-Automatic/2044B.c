#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases should be within the bounds

    for (int TC = 1; TC <= TCS; TC++) {
        char s[101];
        scanf("%s", s);
        int len = strlen(s);
        assert(len >= 1 && len <= 100); // PRE: Length of string should be within the bounds

        for (int i = 0; i < len; i++) {
            if (s[i] == 'p') s[i] = 'q';
            else if (s[i] == 'q') s[i] = 'p';
            // 'w' remains unchanged
        }

        for (int i = len - 1; i >= 0; i--) {
            putchar(s[i]);
        }
        putchar('\n');
    }
    return 0;
    // POST: Output was successfully produced after processing input strings
}