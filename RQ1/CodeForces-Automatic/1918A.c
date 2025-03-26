#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10000
    while (TC--) 
    {
        int n, m;
        scanf("%lld %lld", &n, &m);
        assert(n >= 2 && n <= 10000 && m >= 2 && m <= 10000); // PRE: 2 <= n, m <= 10^4
        printf("%lld\n", n * (m / 2));
        assert(n * (m / 2) == (n * m) / 2); // POST: maximum stability is n * (m / 2)
    }
    return 0;
}