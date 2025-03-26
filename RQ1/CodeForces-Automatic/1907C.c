#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is within the allowed range
    
    while (TC--) {
        int n;
        scanf("%lld", &n);
        
        assert(n >= 1 && n <= 200000); // PRE: Length of string is within the allowed range
        
        char s[200001];
        scanf("%s", s);
        
        int frq[26] = {0};
        int mx = 0;
        
        for (int i = 0; i < n; ++i) {
            frq[s[i] - 'a']++;
            if (frq[s[i] - 'a'] > mx) {
                mx = frq[s[i] - 'a'];
            }
        }
        
        int result;
        if (mx > n / 2) {
            result = 2 * mx - n;
        } else {
            result = n % 2;
        }
        
        printf("%lld\n", result);
        assert(result >= 0); // POST: Result is non-negative, as the minimum length must be >= 0
    }
    return 0;
}