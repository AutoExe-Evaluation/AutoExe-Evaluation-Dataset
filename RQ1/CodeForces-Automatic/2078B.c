#include <stdio.h>
#include <assert.h>

int main()
{
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within limits

    while (TCS--)
    {
        long long n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 2 && n <= 200000); // PRE: n is within limits
        assert(k >= 1 && k <= 1000000000); // PRE: k is within limits

        if (k & 1)
        {
            for (long long i = 0; i < n - 1; i++)
                printf("%lld ", n);
            printf("%lld\n", n - 1);
        }
        else
        {
            for (long long i = 0; i < n - 2; i++)
                printf("%lld ", n - 1);
            printf("%lld %lld\n", n, n - 1);
        }

        // POST: The output should have n integers within the range and not equal to their indices
        // You can replace with actual checks of conditions if needed in a more complex setup.
    }
    
    return 0;
}