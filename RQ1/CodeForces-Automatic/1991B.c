#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4
    
    while (TCS--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 100000); // PRE: 2 ≤ n ≤ 10^5
        
        int b[n - 1];
        for(int i = 0; i < n - 1; ++i) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 0 && b[i] < (1LL << 30)); // PRE: 0 ≤ b_i < 2^30
        }
        
        int a[n];
        a[0] = b[0];
        for(int i = 1; i < n - 1; ++i) 
            a[i] = b[i - 1] | b[i];
        
        a[n - 1] = b[n - 2];
        
        for(int i = 1; i < n; ++i) {
            int x = a[i] & a[i - 1];
            int y = b[i - 1];
            if (x != y) {
                printf("-1\n");
                break; // No good array exists
            }
        }
        
        // POST: Ensuring the output array a is valid
        for(int i = 1; i < n; ++i) {
            int x = a[i] & a[i - 1];
            int y = b[i - 1];
            assert(x == y); // POST: a[i] & a[i - 1] == b[i - 1]
        }
        
        for(int i = 0; i < n; ++i) 
            printf("%lld ", a[i]);
        printf("\n");
    }
    return 0;
}