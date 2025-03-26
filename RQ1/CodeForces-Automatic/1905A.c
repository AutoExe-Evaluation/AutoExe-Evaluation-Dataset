#include <stdio.h>
#include <assert.h>

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

int main() {
    long long TC;
    
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases should be within [1, 10^4]
    
    while (TC--) {
        long long n, m;
        scanf("%lld %lld", &n, &m);
        assert(n >= 2 && n <= 100); // PRE: n should be within [2, 100]
        assert(m >= 2 && m <= 100); // PRE: m should be within [2, 100]

        long long result = max(n, m);
        printf("%lld\n", result);
        assert(result >= 2 && result <= 100); // POST: Minimum rebuilt cities should be at least 2 and at most 100
    }
    return 0;
}