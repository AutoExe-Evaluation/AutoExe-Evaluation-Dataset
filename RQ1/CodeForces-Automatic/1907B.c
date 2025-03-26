#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 ≤ t ≤ 1000

    while (TC--) {
        char s[1000001];
        char ans[1000001];
        int small = 0, capital = 0, ans_index = 0;

        scanf("%s", s);
        int len = strlen(s);
        assert(len > 0); // PRE: each line consists of at least one letter

        for (int i = len - 1; i >= 0; --i) {
            char c = s[i];
            if (islower(c)) {
                if (c == 'b') {
                    small++;
                } else if (small) {
                    small--;
                } else {
                    ans[ans_index++] = c;
                }
            } else {
                if (c == 'B') {
                    capital++;
                } else if (capital) {
                    capital--;
                } else {
                    ans[ans_index++] = c;
                }
            }
        }

        for (int j = ans_index - 1; j >= 0; j--) {
            putchar(ans[j]);
        }
        putchar('\n');
        
        // POST: the output string is correctly processed according to the keyboard behavior
        assert(ans_index >= 0); // There should not be any invalid output length
    }
    return 0;
}