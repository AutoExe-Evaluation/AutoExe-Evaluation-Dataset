#include <stdio.h>

#define int long long

int main()
{
    int TCS = 1;
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4
    scanf("%lld", &TCS);
    for (int TC = 1; TC <= TCS; ++TC)
    {
        int n, m, i, j;
        scanf("%lld %lld %lld %lld", &n, &m, &i, &j);
        assert(n >= 1 && n <= 1000000000); // PRE: 1 ≤ n ≤ 10^9
        assert(m >= 1 && m <= 1000000000); // PRE: 1 ≤ m ≤ 10^9
        assert(i >= 1 && i <= n); // PRE: 1 ≤ i ≤ n
        assert(j >= 1 && j <= m); // PRE: 1 ≤ j ≤ m
        printf("1 1 %lld %lld\n", n, m);
        assert((1 >= 1 && 1 <= n) && (1 >= 1 && 1 <= m)); // POST: yo-yo positions are valid
        assert((n >= 1 && n <= n) && (m >= 1 && m <= m)); // POST: yo-yo positions are valid
    }
    return 0;
}