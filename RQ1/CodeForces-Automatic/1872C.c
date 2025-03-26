#include <stdio.h>
#include <math.h>
#include <assert.h>

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: 1 ≤ t ≤ 500

    while (TC--) {
        int l, r;
        scanf("%d %d", &l, &r);
        assert(l >= 1 && l <= r && r <= 10000000); // PRE: 1 ≤ l ≤ r ≤ 10^7
        
        if (r < 4) {
            printf("-1\n");
        } else if (l == r) {
            if (r <= 1) {
                printf("-1\n");
            } else if (l % 2 == 0) {
                printf("2 %d\n", l - 2);
                assert(gcd(2, l - 2) != 1); // POST: gcd(a,b) ≠ 1
            } else {
                for (int i = 3; i <= sqrt(r); ++i) {
                    int j = l - i;
                    if (gcd(i, j) != 1) {
                        printf("%d %d\n", i, j);
                        assert(gcd(i, j) != 1); // POST: gcd(a,b) ≠ 1
                        return 0;
                    }
                }
                printf("-1\n");
            }
        } else {
            if (r % 2) {
                printf("2 %d\n", r - 3);
                assert(gcd(2, r - 3) != 1); // POST: gcd(a,b) ≠ 1
            } else {
                printf("2 %d\n", r - 2);
                assert(gcd(2, r - 2) != 1); // POST: gcd(a,b) ≠ 1
            }
        }

        assert(l + 2 <= r && l + 2 >= l); // POST: l ≤ a + b ≤ r
    }
    return 0;
}