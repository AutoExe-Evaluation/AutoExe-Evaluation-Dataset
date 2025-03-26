#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

long long gcd(long long a, long long b) {
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 1000); // PRE: 1 ≤ n ≤ 1000
    
    long long *v = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &v[i]);
        assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: 1 ≤ ai ≤ 10^9
    }

    long long *ans = (long long *)malloc((2 * n) * sizeof(long long));
    int ans_size = 0;
    ans[ans_size++] = v[0];

    for (int i = 1; i < n; i++) {
        if (gcd(ans[ans_size - 1], v[i]) > 1) {
            ans[ans_size++] = 1;
        }
        ans[ans_size++] = v[i];
    }

    printf("%d\n", ans_size - n);
    
    // POST: The output array must be co-prime
    for (int i = 0; i < ans_size - 1; i++) {
        assert(gcd(ans[i], ans[i + 1]) == 1); // POST: Any two adjacent numbers are co-prime
    }

    for (int i = 0; i < ans_size; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");

    free(v);
    free(ans);
    return 0;
}