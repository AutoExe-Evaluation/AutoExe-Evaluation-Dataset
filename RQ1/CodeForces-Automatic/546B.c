#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}

int main() {
    long long n;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 3000); // PRE: n is within the specified range

    long long *v = (long long *)malloc(n * sizeof(long long));
    for (long long i = 0; i < n; i++) {
        scanf("%lld", &v[i]);
        assert(v[i] >= 1 && v[i] <= n); // PRE: each badge coolness factor is within the specified range
    }

    qsort(v, n, sizeof(long long), cmp);
    
    long long *used = (long long *)calloc(n + 1, sizeof(long long));
    long long coins = 0;
    for (long long i = 0; i < n; i++) {
        long long x = v[i];
        while (used[x]) {
            x++;
            coins++;
        }
        used[x] = 1;
    }
    
    printf("%lld\n", coins);
    assert(coins >= 0); // POST: the number of coins is non-negative
    
    free(v);
    free(used);
    return 0;
}