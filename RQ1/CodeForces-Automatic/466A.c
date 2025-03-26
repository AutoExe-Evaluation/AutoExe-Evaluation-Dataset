#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main()
{
    int n, m, a, b;
    scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
    
    assert(n >= 1 && n <= 1000); // PRE: n is within the range
    assert(m >= 1 && m <= 1000); // PRE: m is within the range
    assert(a >= 1 && a <= 1000); // PRE: a is within the range
    assert(b >= 1 && b <= 1000); // PRE: b is within the range
    
    long long min_cost = n * a;
    long long f = n / m, r = n % m;

    long long cost1 = r * a + f * b;
    long long cost2 = b * (f + 1);

    if (cost1 < min_cost) min_cost = cost1;
    if (cost2 < min_cost) min_cost = cost2;

    printf("%lld\n", min_cost);
    assert(min_cost >= 0); // POST: Minimum cost must be non-negative
    return 0;
}