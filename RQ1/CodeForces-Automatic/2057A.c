#include <stdio.h>
#include <assert.h>

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases in the range [1, 1000]
    
    for (long long TC = 1; TC <= TCS; ++TC) {
        long long n, m;
        scanf("%lld %lld", &n, &m);
        assert(n >= 1 && n <= 1000000000); // PRE: Rows in the range [1, 10^9]
        assert(m >= 1 && m <= 1000000000); // PRE: Columns in the range [1, 10^9]
        
        long long result = max(m, n) + 1;
        printf("%lld\n", result);
        assert(result == max(m, n) + 1); // POST: Result is the maximum of m or n plus 1
    }
    return 0;
}