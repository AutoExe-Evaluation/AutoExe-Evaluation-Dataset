#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: 1 <= t <= 100

    while (TC--) {
        int n;
        char s[2001];
        scanf("%lld %s", &n, s);
        assert(n >= 1 && n <= 2000); // PRE: 1 <= n <= 2000
        assert(strlen(s) == n); // Check string length matches n
        
        int len = strlen(s);
        
        while (len > 0) {
            char f = s[0];
            char e = s[len - 1];
            if ((f == '0' && e == '1') || (f == '1' && e == '0')) {
                memmove(s, s + 1, len - 1);
                len -= 1;
                s[len] = '\0';
                len -= 1;
            } else {
                break;
            }
        }
        
        printf("%lld\n", len);
        assert(len >= 0); // POST: length of original string is nonnegative
    }
    return 0;
}