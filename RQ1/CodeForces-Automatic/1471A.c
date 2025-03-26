#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int TCS = 1;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases must be in the range [1, 1000]

    for (int TC = 1; TC <= TCS; ++TC)
    {
        int n, x;
        scanf("%lld %lld", &n, &x);
        assert(n >= 1 && n <= 100000); // PRE: Array length must be in the range [1, 10^5]
        assert(x >= 1 && x <= 1000000000); // PRE: x must be in the range [1, 10^9]

        int sum = 0, mx = 0;
        for (int i = 0; i < n; ++i)
        {
            int y;
            scanf("%lld", &y);
            assert(y >= 1 && y <= 1000000000); // PRE: Each element must be in the range [1, 10^9]
            sum += y;
            mx += (y + x - 1) / x;
        }
        int mn = (sum + x - 1) / x;

        printf("%lld %lld\n", mn, mx);
        assert(mn >= 1 && mn <= n); // POST: Minimum beauty must be at least 1 and at most n
        assert(mx >= 1 && mx <= 100000); // POST: Maximum beauty must be at least 1 and can realistically be at most 100,000 based on problem constraints
    }
}