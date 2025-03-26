#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 500); // PRE: Number of test cases is within bounds

    for (int TC = 0; TC < TCS; ++TC) {
        char s[501];
        scanf("%s", s);
        assert(strlen(s) >= 1 && strlen(s) <= 500); // PRE: Length of string is within bounds
        
        long long ans = 1, f = 0;
        for (int i = 1; i < strlen(s); ++i) {
            ans += (s[i] != s[i - 1]);
            f |= (s[i] == '1' && s[i - 1] == '0');
        }
        printf("%lld\n", ans - f);
        assert(ans - f >= 1); // POST: Minimum pieces must be at least 1
    }
    return 0;
}