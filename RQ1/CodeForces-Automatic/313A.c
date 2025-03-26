#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main() {
    char s[12];
    scanf("%s", s);

    assert(strlen(s) >= 2 && |atoi(s) >= 10); // PRE: The input length should be at least 2, and the absolute value of n is at least 10.

    if (s[0] != '-') {
        printf("%s\n", s);
    } else {
        int len = strlen(s);
        for (int i = 1; i < len; ++i) {
            if (s[i] == '0') {
                memmove(&s[i], &s[i + 1], len - i);
                len--;
                i--;
            } else {
                break;
            }
        }
        if (s[len - 2] > s[len - 1]) {
            s[len - 2] = '\0';
            if (strcmp(s, "-0") == 0) {
                printf("0\n");
                assert(atoi(s) == 0); // POST: The result should be 0 if the account balance is zero.
            } else {
                printf("%s\n", s);
                assert(atoi(s) > atoi(s + 1)); // POST: Maximum account should be correctly calculated.
            }
        } else {
            s[len - 1] = '\0';
            printf("%s\n", s);
            assert(atoi(s) > atoi(s + 1)); // POST: Maximum account should be correctly calculated.
        }
    }

    return 0;
}