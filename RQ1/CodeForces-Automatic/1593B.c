#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

long long count(char *s, char *t) {
    int ct = 0;
    int slen = strlen(s);
    int tlen = strlen(t);
    while (slen && tlen) {
        if (s[slen - 1] == t[tlen - 1]) {
            tlen--;
        } else {
            ct++;
        }
        slen--;
    }
    if (tlen) return INT_MAX;
    return ct;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 10000); // PRE: number of test cases within bounds
    for (int TC = 1; TC <= TCS; ++TC) {
        char s[20];
        scanf("%s", s);
        
        assert(strlen(s) > 0); // PRE: input string is not empty
        assert(strlen(s) <= 18); // PRE: input number does not exceed 10^18
        
        char *v[] = {"00", "25", "50", "75"};
        long long mn = INT_MAX;
        for (int i = 0; i < 4; ++i) {
            mn = (count(s, v[i]) < mn) ? count(s, v[i]) : mn;
        }
        printf("%lld\n", mn);
        
        assert(mn >= 0); // POST: minimum number of steps is non-negative
    }
    return 0;
}