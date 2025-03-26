#include <stdio.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases should be in range [1, 100]

    for (long long TC = 1; TC <= TCS; ++TC) {
        long long r, g, b;
        scanf("%lld %lld %lld", &r, &g, &b);
        assert(r >= 1 && r <= 1000000000); // PRE: Number of red lamps should be in range [1, 10^9]
        assert(g >= 1 && g <= 1000000000); // PRE: Number of green lamps should be in range [1, 10^9]
        assert(b >= 1 && b <= 1000000000); // PRE: Number of blue lamps should be in range [1, 10^9]

        if (r > b + g + 1 || b > r + g + 1 || g > r + b + 1) {
            printf("NO\n");
            assert(1); // POST: There exists at least one pair of lamps of the same color adjacent to each other
        } else {
            printf("YES\n");
            assert(0); // POST: No pairs of lamps of the same color adjacent to each other
        }
    }
    return 0;
}