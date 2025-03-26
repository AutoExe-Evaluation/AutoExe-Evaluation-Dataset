#include <stdio.h>
#include <assert.h>

#define int long long
#define M 1000000007

int main()
{
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: Number of test cases is within valid range

    while (TC--)
    {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100); // PRE: Array length is within valid range

        int prod = 1;
        for (int i = 0; i < n; ++i)
        {
            int x;
            scanf("%lld", &x);
            assert(x >= -1000000000 && x <= 1000000000); // PRE: Each a_i is within valid range
            prod = (prod * x) % M;
        }

        if (prod > 0)
        {
            printf("1\n1 0\n");
            assert(prod == 0); // POST: Minimum product is achieved and is 0
        }
        else
        {
            printf("0\n");
            assert(prod <= 0); // POST: Minimum product is already non-positive
        }
    }
    return 0;
}