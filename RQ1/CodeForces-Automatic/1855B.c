#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 1000000000000000000); // PRE: 1 ≤ n ≤ 10^18

        for (int i = 1; i < 100; i++) {
            if (n % i) {
                printf("%lld\n", i - 1);
                assert(i - 1 >= 0 && i - 1 < 100); // POST: size of interval is valid
                break;
            }
        }
    }
    return 0;
}