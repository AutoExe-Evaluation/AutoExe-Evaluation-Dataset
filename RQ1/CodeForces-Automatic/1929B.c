#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be in range

    while (TC--) {
        int n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 2 && n <= 100000000 && k >= 1 && k <= 4 * n - 2); // PRE: Valid n and k

        int x = 2 * (n + n - 2);
        if (k <= x) {
            if (k & 1)
                k++;
            printf("%lld\n", k / 2);
            assert(k / 2 >= 0); // POST: The output must be non-negative
        } else {
            printf("%lld\n", x / 2 + (k - x));
            assert(x / 2 + (k - x) >= 0); // POST: The output must be non-negative
        }
    }
    return 0;
}