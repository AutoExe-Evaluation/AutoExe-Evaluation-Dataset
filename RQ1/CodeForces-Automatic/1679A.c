#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases is within limits
    while (TC--)
    {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 1000000000000000000); // PRE: Total number of wheels is within limits
        if (n & 1 || n < 4)
        {
            printf("-1\n");
            continue; // No valid bus configurations
        }
        int mn = n / 6;
        int mx = n / 4;
        if (n % 6)
            mn++;
        printf("%lld %lld\n", mn, mx);
        assert(mn >= 1 && mx >= mn); // POST: Minimum is at least 1 and max is not less than min
    }
    return 0;
}