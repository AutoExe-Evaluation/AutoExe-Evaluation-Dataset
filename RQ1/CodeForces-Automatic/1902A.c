#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases is between 1 and 100
    while (TC--) {
        int n;
        char s[101];
        scanf("%lld %s", &n, s);
        assert(n >= 1 && n <= 100); // PRE: Length of string is between 1 and 100
        assert(strlen(s) == n); // PRE: Length of the string matches the given n

        int zero_count = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                zero_count++;
            }
        }
        
        if (zero_count > 0) {
            printf("YES\n");
            assert(zero_count > 0); // POST: If there is at least one '0', output is "YES"
        } else {
            printf("NO\n");
            assert(zero_count == 0); // POST: If there are no '0's, output is "NO"
        }
    }
    return 0;
}