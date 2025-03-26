#include <stdio.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 104); // PRE: Number of test cases must be in range [1, 104]

    while (TCS--) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 200000); // PRE: n must be in range [2, 200000]
        long long v[n];

        for (long long i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: Each element must be in range [1, 10^9]
        }

        for (long long i = 1; i < n; ++i) {
            if (v[i - 1] > v[i]) {
                printf("NO\n");
                return 0; // POST: If sequence is not non-decreasing, output "NO"
            }
            v[i] -= v[i - 1];
        }

        printf("YES\n"); // POST: If all elements can be made non-decreasing, output "YES"
    }
    return 0;
}