#include <stdio.h>
#include <string.h>
#include <assert.h>

void solve() {
    char s[31], t[31];
    scanf("%s %s", s, t);
    int m[26] = {0};

    // PRE: s and t are non-empty strings of uppercase letters
    assert(strlen(s) > 0 && strlen(t) > 0);
    
    for (int i = 0; s[i]; i++)
        m[s[i] - 'A']++;

    for (int i = 0; t[i]; i++)
        m[t[i] - 'A']--;

    for (int i = 0; i < 26; i++) {
        int count = m[i];
        if (count > 0) {
            for (int j = 0; s[j]; j++) {
                if (s[j] == (i + 'A') && count > 0) {
                    memmove(&s[j], &s[j + 1], strlen(s) - j);
                    count--;
                    j--;
                }
            }
        }
    }
    // POST: if we can form t from s, s should equal to t after modifications
    assert(strcmp(s, t) == 0 || strlen(s) >= strlen(t)); // ensures s can be transformed to match t
    printf("%s\n", strcmp(s, t) == 0 ? "YES" : "NO");
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    
    // PRE: TCS should be between 1 and 10000
    assert(TCS >= 1 && TCS <= 10000);
    
    for (int TC = 1; TC <= TCS; TC++) {
        solve();
    }
    return 0;
}