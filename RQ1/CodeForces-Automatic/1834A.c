#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: number of test cases is within the bounds
    while (TC--) 
    {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100); // PRE: array length is within the bounds
        int prod = 1, sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int x;
            scanf("%lld", &x);
            assert(x == 1 || x == -1); // PRE: elements are either 1 or -1
            prod *= x;
            sum += x;
        }
        for (int i = 0; ; ++i)
        {
            if (sum >= 0 && prod == 1)
            {
                printf("%lld\n", i);
                assert(i >= 0); // POST: minimum operations are non-negative
                break;
            }
            prod *= -1;
            sum += 2;
        }
    }
    return 0;
}