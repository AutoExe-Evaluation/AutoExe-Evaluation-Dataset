#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is valid

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 30); // PRE: Size of the array is valid

        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 0 && v[i] <= 2000000000); // PRE: Array elements are valid
        }

        int ans = 0;
        for (int i = n - 2; i >= 0; --i) {
            while (v[i] >= v[i + 1] && v[i] > 0) {
                v[i] >>= 1;
                ans++;
            }
            if (v[i] == v[i + 1]) {
                printf("-1\n");
                free(v);
                break; // Exit without printing the answer
            }
        }
        // POST: Sequence should be strictly increasing
        if (ans > 0 && v[0] < v[1]) {
            printf("%lld\n", ans);
        }
        else if (v[0] < v[1]) {
            printf("%lld\n", ans);
        } else {
            printf("-1\n");
        }

        free(v);
    }
    return 0;
}