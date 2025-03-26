#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_N 200000

int main() {
    long long TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases should be between 1 and 10^4

    while (TC--) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Number of glasses should be between 1 and 2 * 10^5
        
        long long *v = (long long *)malloc(n * sizeof(long long));
        for(long long i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: Juice amount should be between 1 and 10^9
        }

        long long *st = (long long *)malloc((n + 1) * sizeof(long long));
        st[0] = 1;
        long long sum = 0;
        int found = 0;

        for(long long i = 0; i < n; ++i) {
            if(i & 1) {
                v[i] *= -1;
            }
            sum += v[i];

            for (long long j = 0; j <= i; j++) {
                if (st[j] == sum) {
                    printf("YES\n");
                    found = 1;
                    break;
                }
            }

            if (found) break;
            st[i + 1] = sum;
        }

        if (!found) {
            printf("NO\n");
        }

        free(v);
        free(st);
    }

    // Post-condition: Output should be correct based on the input constraints
    // However, this cannot be easily asserted in C without explicitly checking conditions,
    // as we cannot mathematically guarantee the correctness of the solution without actual tests.
    return 0;
}