#include <stdio.h>
#include <assert.h>

int main()
{
    long long TCS = 1;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases should be within limits

    for (long long TC = 1; TC <= TCS; ++TC)
    {
        long long n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100); // PRE: Each value of n should be within limits

        if (n & 1)
        {
            printf("Kosuke\n");
            assert(n % 2 != 0); // POST: If n is odd, Kosuke makes the last turn
        }
        else
        {
            printf("Sakurako\n");
            assert(n % 2 == 0); // POST: If n is even, Sakurako makes the last turn
        }
    }

    return 0;
}