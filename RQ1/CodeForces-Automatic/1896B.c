#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    long long TC;
    scanf("%lld", &TC); // PRE: TC should be >= 1 and <= 1000
    
    while (TC--) {
        long long n;
        scanf("%lld", &n); // PRE: n should be >= 2 and <= 200000
        char s[200001];
        scanf("%s", s); // PRE: s should consist of 'A' and 'B' with length n

        long long pta = n, ptb = 0;
        
        for (long long i = 0; i < n; ++i) {
            if (s[i] == 'A') {
                if (i < pta) {
                    pta = i;
                }
            }
            if (s[i] == 'B') {
                if (i > ptb) {
                    ptb = i;
                }
            }
        }
        
        // POST: max_operations is equal to the difference between positions of last 'B' and first 'A'
        long long max_operations = (pta > ptb) ? 0 : ptb - pta; 
        printf("%lld\n", max_operations);
        assert(max_operations >= 0); // POST: max_operations should be non-negative
    }
    
    return 0;
}