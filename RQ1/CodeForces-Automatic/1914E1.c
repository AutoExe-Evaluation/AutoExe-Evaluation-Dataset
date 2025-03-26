#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be between 1 and 1000

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 6); // PRE: Number of colors should be between 2 and 6

        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: a_i should be between 1 and 10^9
        }
        for (int i = 0; i < n; i++) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: b_i should be between 1 and 10^9
        }

        int *s = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            s[i] = a[i] + b[i];
        }

        int t = 1, ans = 0;
        while (1) {
            int maxIndex = -1;
            for (int i = 0; i < n; i++) {
                if (s[i] > 0 && (maxIndex == -1 || s[i] > s[maxIndex])) {
                    maxIndex = i;
                }
            }
            if (maxIndex == -1) {
                break;
            }

            if (t) {
                ans += a[maxIndex] - 1;
            } else {
                ans -= b[maxIndex] - 1;
            }
            s[maxIndex] = 0;
            t ^= 1;
        }

        printf("%lld\n", ans);
        assert(ans >= -1000000000 && ans <= 1000000000); // POST: The score should be within reasonable bounds
        free(a);
        free(b);
        free(s);
    }
    return 0;
}