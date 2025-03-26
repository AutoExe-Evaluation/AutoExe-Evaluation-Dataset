#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300000

int main() {
    long long TC;
    scanf("%lld", &TC);

    // PRE: The number of test cases and the respective input for each test case must be valid.
    assert(TC >= 1 && TC <= 30000); // PRE: Number of test cases is within bounds

    while (TC--) {
        long long n, k;
        scanf("%lld %lld", &n, &k);

        assert(n >= 1 && n <= 300000); // PRE: Number of monsters is within bounds
        assert(k >= 1 && k <= 2000000000); // PRE: Maximum bullets k is within bounds

        long long a[MAX_N], b[MAX_N + 1] = {0};

        for(long long i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: Health of monsters is within bounds
        }

        for(long long i = 0; i < n; i++) {
            long long x;
            scanf("%lld", &x);
            assert(x != 0 && abs(x) <= n); // PRE: Monsters' positions are valid and not zero
            b[abs(x)] += a[i];
        }

        long long r = 0;
        for(long long i = 1; i <= n; i++) {
            r += k;
            if(r < b[i]) {
                printf("NO\n");
                return 0; // POST: If we cannot kill all monsters in time
            }
            r -= b[i];
        }
        
        printf("YES\n"); // POST: If all monsters can be killed in time
    }

    return 0;
}