#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long max_element(long long *arr, int size) {
    long long max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 20000); // PRE: 1 <= t <= 2 * 10^4
    
    while (TCS--) {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 100000); // PRE: 1 <= n <= 10^5
        assert(m >= 1 && m <= 100000); // PRE: 1 <= m <= 10^5
        
        long long *v = (long long *)malloc(n * sizeof(long long));
        for (int i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }

        long long mx = max_element(v, n);
        
        for (int i = 0; i < m; i++) {
            char c;
            long long l, r;
            scanf(" %c %lld %lld", &c, &l, &r);
            assert(c == '+' || c == '-'); // PRE: c in {+, -}
            assert(l >= 1 && r >= l && r <= 1000000000); // PRE: 1 <= l <= r <= 10^9

            if (c == '+') {
                if (mx <= r && mx >= l) {
                    mx++;
                }
            } else {
                if (mx >= l && mx <= r) {
                    mx--;
                }
            }
            printf("%lld ", mx);
        }
        printf("\n");
        free(v);
        assert(mx <= 1000000000); // POST: max value should be within limits
    }
    return 0;
}