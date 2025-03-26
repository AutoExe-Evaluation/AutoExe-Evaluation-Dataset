#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_SIZE 200005

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within bounds

    while (TCS--) {
        char s[MAX_SIZE], t[MAX_SIZE];
        scanf("%s %s", s, t);
        
        int i = 0, j = 0;
        assert(strlen(s) >= 1 && strlen(s) <= 200000); // PRE: Length of string s is within bounds
        assert(strlen(t) >= 1 && strlen(t) <= strlen(s)); // PRE: Length of string t is within bounds
        
        while (s[i] != '\0' && t[j] != '\0') {
            if (s[i] == t[j]) j++;
            else if (s[i] == '?') s[i] = t[j++];
            i++;
        }
        
        while (s[i] != '\0') {
            if (s[i] == '?') s[i] = 'a';
            i++;
        }
        
        if (t[j] == '\0') {
            printf("YES\n%s\n", s);
            assert(strstr(s, t) != NULL); // POST: t is a subsequence of s
        } else {
            printf("NO\n");
            assert(t[j] != '\0'); // POST: t is not a subsequence of s
        }
    }
    return 0;
}