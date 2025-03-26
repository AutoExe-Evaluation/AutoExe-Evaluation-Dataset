#include <stdio.h>
#include <string.h>
#include <assert.h>

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    // PRE: Ensure that the number of test cases is within the allowed range
    int TCS = 1;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000);

    while(TCS--) {
        char a[101], b[101];
        scanf("%s %s", a, b);
        
        // Ensure the strings are within the allowed lengths
        assert(strlen(a) >= 1 && strlen(a) <= 100);
        assert(strlen(b) >= 1 && strlen(b) <= 100);
        
        int n = strlen(a), m = strlen(b);
        long long mn = m + n;

        for(int i = 0; i < m; i++) {
            int k = i;
            for(int j = 0; j < n; j++) {
                if(k < m && a[j] == b[k]) k++;
            }
            mn = min(mn, n + m - k + i);
        }
        
        // POST: The result should be at least the length of a
        assert(mn >= n); // Ensuring the substring 'a' length is counted in the result
        printf("%lld\n", mn);
    }
    return 0;
}