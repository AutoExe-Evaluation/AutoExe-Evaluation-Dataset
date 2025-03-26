#include <stdio.h>
#include <assert.h>

int main() {
    long long n;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 100000); // PRE: 1 <= m <= 10^5
    
    long long v[31] = {0};
    
    for(long long i = 0; i < n; ++i) {
        long long t, x;
        scanf("%lld %lld", &t, &x);
        assert((t == 1 && x >= 0 && x <= 29) || (t == 2 && x >= 0 && x <= 1000000000)); // PRE: Correct types of queries
        
        if(t == 1) 
            v[x]++;
        else {
            long long original_x = x; // Store original value of x for postcondition check
            for(long long j = 29; j >= 0; --j) {
                long long mx = (x >> j) < v[j] ? (x >> j) : v[j];
                x -= mx * (1LL << j);
            }
            printf("%s\n", (x == 0) ? "YES" : "NO");
            assert(x == 0 || (original_x > 0 && x != 0)); // POST: If x was possible, should result in x == 0
        }
    }
    return 0;
}