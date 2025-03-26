#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 100

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: Number of test cases must be between 1 and 500
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 100); // PRE: Length of array must be between 2 and 100
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000); // PRE: Elements must be positive integers ≤ 10^6
        }
        int possible = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (gcd(v[i], v[j]) <= 2) {
                    possible = 1;
                    break;
                }
            }
            if (possible) break;
        }
        if (possible) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        free(v);
    }
    assert(TC == 0); // POST: All test cases processed
    return 0;
}