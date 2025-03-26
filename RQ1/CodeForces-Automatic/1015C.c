#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int compare(const void *a, const void *b) {
    return (*(long long *)b - *(long long *)a);
}

int main() {
    int n, m;
    long long s = 0;
    scanf("%d %d", &n, &m);
    
    assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 10^5
    assert(m >= 1 && m <= 1000000000); // PRE: 1 ≤ m ≤ 10^9

    long long *v = (long long *)malloc(n * sizeof(long long));
    
    for (int i = 0; i < n; ++i) {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        assert(a > b && a >= 1 && a <= 1000000000); // PRE: a_i > b_i and 1 ≤ a_i ≤ 10^9
        assert(b >= 1 && b <= 1000000000); // PRE: 1 ≤ b_i ≤ 10^9
        long long d = a - b;
        v[i] = d;
        s += a;
    }
    
    if (s <= m) {
        printf("0\n");
        free(v);
        return 0;
    }
    
    qsort(v, n, sizeof(long long), compare);
    
    for (int i = n - 1; i >= 0; --i) {
        s -= v[i];
        if (s <= m) {
            printf("%d\n", i + 1);
            free(v);
            return 0;
        }
    }
    
    printf("-1\n");
    free(v);
    return 0;
    // POST: result is either the minimum number of songs to compress or -1
}