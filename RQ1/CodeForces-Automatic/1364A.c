#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    long long t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 5); // PRE: 1 <= t <= 5

    while (t--) {
        long long n, x, sum = 0;
        scanf("%lld %lld", &n, &x);
        assert(n >= 1 && n <= 100000); // PRE: 1 <= n <= 100000
        assert(x >= 1 && x <= 10000); // PRE: 1 <= x <= 10000

        long long *a = (long long *)malloc(n * sizeof(long long));
        long long *st = (long long *)malloc(n * sizeof(long long));
        long long st_size = 0;

        for (long long i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 0 && a[i] <= 10000); // PRE: 0 <= a[i] <= 10000

            if (a[i] % x) {
                st[st_size++] = i;
                st[st_size++] = n - i - 1;
            }
            sum += a[i];
        }

        long long result;
        if (sum % x) {
            result = n;
        } else if (st_size == 0) {
            result = -1;
        } else {
            long long max_index = st[0];
            for (long long i = 1; i < st_size; i++) {
                if (st[i] > max_index) {
                    max_index = st[i];
                }
            }
            result = max_index;
        }
        
        printf("%lld\n", result);
        assert(result == -1 || result <= n); // POST: result is -1 or result <= n

        free(a);
        free(st);
    }

    return 0;
}