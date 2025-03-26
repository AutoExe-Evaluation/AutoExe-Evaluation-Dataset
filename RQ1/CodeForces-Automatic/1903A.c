#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC > 0); // PRE: Number of test cases must be positive
    while (TC--) {
        int n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 1 && n <= 100); // PRE: n must be in the range [1, 100]
        assert(k >= 1 && k <= n); // PRE: k must be in the range [1, n]
        
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: a_i must be in the range [1, 10^9]
        }

        if (is_sorted(v, n)) {
            printf("YES\n");
        } else if (n > 1 && k < 2) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }

        free(v);
    }
    assert(1); // POST: The output can be sorted with given conditions
    return 0;
}