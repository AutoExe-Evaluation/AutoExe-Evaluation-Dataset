#include <stdio.h>
#include <assert.h>

#define ll long long

int main()
{
    ll n, m, k, l;
    scanf("%lld%lld%lld%lld", &n, &m, &k, &l);
    
    assert(n >= k); // PRE: Number of different coins is at least equal to the size of Ivan's collection
    assert(m > 0 && l >= 0); // PRE: Number of friends must be positive and least new coins must be non-negative

    ll x = (l + k) / m;
    if ((l + k) % m)
        x++;
    
    if (x * m > n || n < l + k || n < m)
        printf("-1\n");
    else {
        printf("%lld\n", x);
        assert(x * m <= n); // POST: The total number of coins given must not exceed the number of different coins
        assert(n >= l + k); // POST: The total number of different coins must be at least the sum of new and owned coins
        assert(n >= m); // POST: The total number of different coins must be at least equal to the number of friends
    }

    return 0;
}