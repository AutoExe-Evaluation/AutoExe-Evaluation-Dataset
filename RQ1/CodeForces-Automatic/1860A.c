#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    char s[51], t[101];
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases is within bounds

    while (TC--) {
        scanf("%s", s);
        assert(strlen(s) >= 2 && strlen(s) <= 50); // PRE: Length of string s is within bounds
        int close = 0, open = 0, nested = 0, len = strlen(s);
        
        for (int i = 1; i < len; ++i) {
            if (s[i] == s[i - 1])
                nested = 1;
        }
        if (strcmp(s, "()") == 0) {
            printf("NO\n");
            continue;
        }

        printf("YES\n");
        if (nested) {
            for (int i = 0; i < len; ++i) {
                t[2 * i] = '(';
                t[2 * i + 1] = ')';
            }
            t[2 * len] = '\0';
            printf("%s\n", t);
        } else {
            for (int i = 0; i < len; ++i)
                t[i] = '(';
            for (int i = 0; i < len; ++i)
                t[len + i] = ')';
            t[2 * len] = '\0';
            printf("%s\n", t);
        }

        // POST: The length of t should be 2 * length of s and should not contain s as a substring
        assert(strlen(t) == 2 * len); // POST: Length of generated string t is double that of input string s
        assert(strstr(t, s) == NULL); // POST: String s should not be a substring of t
    }
    return 0;
}