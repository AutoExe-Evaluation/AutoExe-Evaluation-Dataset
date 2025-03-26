#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 200000

int compare(const void* a, const void* b) {
    if (*(long long*)a > *(long long*)b) return 1;
    if (*(long long*)a < *(long long*)b) return -1;
    return 0;
}

int main() {
    long long TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: 1 <= t <= 100

    while (TC--) {
        long long n, m;
        scanf("%lld %lld", &n, &m);
        assert(n >= 1 && n <= m && m <= 200000); // PRE: 1 <= n <= m <= 200000

        long long a[MAX], b[MAX];
        
        for (long long i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }
        for (long long i = 0; i < m; i++) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: 1 <= b_i <= 10^9
        }
        
        qsort(a, n, sizeof(long long), compare);
        qsort(b, m, sizeof(long long), compare);
        
        long long ans = 0;
        long long la = 0, ra = n - 1, lb = 0, rb = m - 1;
        
        while (la <= ra) {
            long long l = llabs(a[la] - b[rb]);
            long long r = llabs(a[ra] - b[lb]);
            
            if (l >= r) {
                ans += l;
                la++;
                rb--;
            } else {
                ans += r;
                ra--;
                lb++;
            }
        }
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: D >= 0
    }
    return 0;
}