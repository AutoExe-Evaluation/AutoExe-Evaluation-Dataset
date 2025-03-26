#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS); // PRE: 1 <= TCS <= 10^4

    while (TCS--) {
        long long n;
        scanf("%lld", &n); // PRE: 1 <= n <= 2 * 10^5
        long long *v = (long long*)malloc(n * sizeof(long long));
        long long *m = (long long*)calloc(n + 1, sizeof(long long));
        long long *used = (long long*)calloc(n + 1, sizeof(long long));
        long long ct = 0;

        for (long long i = 0; i < n; ++i) {
            long long x;
            scanf("%lld", &x); // PRE: 1 <= a_i <= n
            assert(x >= 1 && x <= n); // PRE: Each a_i must be within the range
            v[i] = x;
            m[x]++;
        }

        for (long long i = 1; i <= n; ++i) {
            if (m[i] > 0) ct++;
        }

        long long x = 1;
        long long *num = (long long*)malloc(n * sizeof(long long));
        long long numIndex = 0;

        while (ct < n) {
            if (m[x] == 0) {
                num[numIndex++] = x;
                ct++;
            }
            x++;
        }

        for (long long i = 0; i < n; ++i) {
            if (m[v[i]] > 0 && used[v[i]] == 0) {
                printf("%lld ", v[i]);
                used[v[i]]++;
            } else {
                printf("%lld ", num[numIndex - 1]);
                numIndex--;
            }
        }
        printf("\n");

        free(v);
        free(m);
        free(used);
        free(num);

        assert(numIndex >= 0); // POST: numIndex should not be negative, ensuring the integrity of the output
    }
    return 0;
}