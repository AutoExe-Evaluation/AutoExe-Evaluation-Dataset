#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long lcm(long long a, long long b) {
    return (a / __gcd(a, b)) * b;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4
    for (int TC = 1; TC <= TCS; ++TC) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: 1 ≤ n ≤ 50
        int *v = (int *)malloc(n * sizeof(int));
        long long l = 1;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 2 && v[i] <= 20); // PRE: 2 ≤ k_i ≤ 20
            l = lcm(l, v[i]);
        }
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += l / v[i];
        }
        if (sum >= l) {
            printf("-1\n");
            free(v);
            continue;
        }
        for (int i = 0; i < n; ++i) {
            printf("%lld ", l / v[i]);
        }
        printf("\n");
        free(v);
    }
    return 0;
} // POST: The bets are such that for each k_i, the total bet is strictly less than l / v[i]