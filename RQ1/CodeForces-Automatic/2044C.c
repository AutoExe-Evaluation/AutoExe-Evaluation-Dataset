#include <stdio.h>
#include <assert.h>

typedef long long ll;

int main()
{
    ll TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within valid range
    while (TCS--)
    {
        ll m, a, b, c;
        scanf("%lld %lld %lld %lld", &m, &a, &b, &c);
        assert(m >= 1 && m <= 100000000 && a >= 1 && a <= 100000000 && b >= 1 && b <= 100000000 && c >= 1 && c <= 100000000); // PRE: All inputs are within valid range
        
        ll r1 = m > a ? m - a : 0;
        ll r2 = m > b ? m - b : 0;
        ll result = (b < m ? b : m) + (a < m ? a : m) + (c < r1 + r2 ? c : r1 + r2);
        printf("%lld\n", result);
        
        assert(result >= 0); // POST: The result should be non-negative
    }
    return 0;
}