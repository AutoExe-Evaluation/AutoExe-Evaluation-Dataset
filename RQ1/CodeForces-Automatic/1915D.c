#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH 200005

int is_v(char ch) {
    return ch == 'a' || ch == 'e';
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases should be within valid limits
    while (TC--) {
        int n;
        char s[MAX_LENGTH], ans[MAX_LENGTH * 2];
        scanf("%d %s", &n, s);
        
        assert(n >= 1 && n <= 200000); // PRE: Length of the word should be within valid limits

        int index = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (is_v(s[i]) && !is_v(s[i - 1])) {
                ans[index++] = s[i];
                ans[index++] = s[i - 1];
                ans[index++] = '.';
                --i;
            } else {
                ans[index++] = s[i];
            }
        }
        
        if (ans[index - 1] == '.') index--; // Remove last dot if present
        for (int i = index - 1; i >= 0; i--) {
            putchar(ans[i]);
        }
        putchar('\n');
    }
    assert(TC >= 1 && TC <= 100); // POST: At least one test case should be processed
    return 0;
}