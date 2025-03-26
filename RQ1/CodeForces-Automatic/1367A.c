#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 ≤ t ≤ 1000

    for (int TC = 1; TC <= TCS; ++TC) {
        char s[101];
        scanf("%s", s);
        assert(strlen(s) >= 2 && strlen(s) <= 100); // PRE: 2 ≤ |b| ≤ 100

        putchar(s[0]);
        for (int i = 1; i < strlen(s) - 1; i += 2) {
            putchar(s[i]);
        }
        putchar(s[strlen(s) - 1]);
        putchar('\n');
    }
    
    // POST: The output string a satisfies the condition based on input string b
    return 0;
}