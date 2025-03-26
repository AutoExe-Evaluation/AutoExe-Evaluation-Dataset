#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TCS = 1;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ TCS ≤ 10^4

    for (int TC = 1; TC <= TCS; ++TC) {
        char s[51];
        scanf("%s", s);
        assert(strlen(s) >= 1 && strlen(s) <= 50); // PRE: 1 ≤ |s| ≤ 50
        
        int ct = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            assert(s[i] == '0' || s[i] == '1'); // PRE: Characters must be '0' or '1'
            if (s[i] == '1')
                ct++;
        }
        
        printf("%lld\n", ct);
        
        assert(ct <= 50); // POST: Minimum operations cannot exceed the length of the string
    }
    return 0;
}