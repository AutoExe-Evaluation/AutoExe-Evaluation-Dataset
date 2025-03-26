#include<stdio.h>
#include<assert.h>

#define ll long long

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Ensure query count is within bounds
    while (TC--) {
        ll a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        assert(a >= 1 && a <= 10000000000000000LL); // PRE: Ensure a is within bounds
        assert(b >= 1 && b <= 10000000000000000LL); // PRE: Ensure b is within bounds
        assert(c >= 1 && c <= 10000000000000000LL); // PRE: Ensure c is within bounds
        
        ll ans = (a + b + c) / 2;
        printf("%lld\n", ans);
        assert(ans >= 0 && ans <= (a + b + c) / 2); // POST: Ensure ans is valid
    }
    return 0;
}