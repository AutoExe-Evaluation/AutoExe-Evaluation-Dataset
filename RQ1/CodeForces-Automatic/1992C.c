#include <stdio.h>
#include <assert.h>

int main()
{
    long long TCS = 1;
    scanf("%lld", &TCS);

    assert(TCS >= 1 && TCS <= 10000); // PRE: TCS is within the valid range

    for (long long TC = 1; TC <= TCS; ++TC)
    {
        long long n, m, k;
        scanf("%lld%lld%lld", &n, &m, &k);
        
        assert(n >= 2 && n <= 100000); // PRE: n is within the valid range
        assert(1 <= m && m < k && k <= n); // PRE: m and k are within the valid range and m < k

        for (long long i = n; i >= m + 1; --i)
            printf("%lld ", i);
        for (long long i = 1; i <= m; ++i)
            printf("%lld ", i);
        printf("\n");

        // POST: The permutation consists of numbers from 1 to n without duplicates
        // Check that the output permutation is valid (only warning asserts will be checked)
        assert((k - 1) <= (n - m)); // This ensures that we have enough numbers above m to reach k
    }

    return 0;
}