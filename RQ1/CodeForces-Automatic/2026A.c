#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 5000); // PRE: 1 <= TCS <= 5000

    for (int TC = 1; TC <= TCS; ++TC) {
        int x, y, k;
        scanf("%lld %lld %lld", &x, &y, &k);
        assert(x >= 1 && x <= 1000 && y >= 1 && y <= 1000); // PRE: 1 <= x, y <= 1000
        assert(k >= 1 && k <= 1414); // PRE: 1 <= k <= 1414
        
        int m = (x < y) ? x : y;
        printf("0 0 %lld %lld\n", m, m);
        printf("%lld 0 0 %lld\n", m, m);
        
        // POST: Length of segments AB and CD at least K
        // Length of AB = m, Length of CD = m
        assert(m >= k); // Ensure length of segments is at least K
    }
    return 0;
}