#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    long long TCS = 1;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: number of test cases must be within the bounds
    for (long long TC = 1; TC <= TCS; ++TC) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: size of the array must be within the bounds
        long long *v = (long long *)malloc(n * sizeof(long long));
        long long mx = -1;
        long long count = 0;

        for (long long i = 0; i < n; ++i) {
            long long x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: element of the array must be within the bounds
            if (x % 2 == 0) {
                v[count++] = x;
            } else if (x > mx) {
                mx = x;
            }
        }

        if (count == 0 || mx == -1) {
            printf("0\n");
            free(v);
            continue;
        }

        for (long long i = 0; i < count; ++i) {
            if (v[i] < mx) {
                mx += v[i];
            } else {
                printf("%lld\n", count + 1);
                free(v);
                continue;
            }
        }

        printf("%lld\n", count);
        free(v);
        assert(count >= 0); // POST: count should be non-negative
    }
    return 0;
}