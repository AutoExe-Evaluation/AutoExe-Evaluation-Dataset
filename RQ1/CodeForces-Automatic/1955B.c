#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 1000000007

typedef long long ll;

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases should be between 1 and 10^4

    while (TC--) {
        ll n, c, d;
        scanf("%lld%lld%lld", &n, &c, &d);
        assert(n >= 2 && n <= 500); // PRE: Size of square should be between 2 and 500
        assert(c >= 1 && c <= 1000000); // PRE: c should be between 1 and 10^6
        assert(d >= 1 && d <= 1000000); // PRE: d should be between 1 and 10^6
        
        ll *m = (ll *)calloc(n * n + 1, sizeof(ll)); // Allocate space for counting occurrences
        for (ll i = 0; i < n * n; ++i) {
            ll x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: Elements of b should be between 1 and 10^9
            m[x]++;
        }

        ll p = 0;
        while (m[p] == 0) p++;
        m[p]--;

        for (ll i = 0; i < n; ++i) {
            ll q = p;
            for (ll j = 0; j < n - 1; ++j) {
                if (m[q + d] == 0) {
                    printf("NO\n");
                    free(m);
                    return 0; 
                }
                m[q + d]--;
                q += d;
            }
            if (m[p + c] == 0 && i < n - 1) {
                printf("NO\n");
                free(m);
                return 0; 
            }
            m[p + c]--;
            p += c;
        }
        printf("YES\n");
        free(m);
    }
    
    return 0;
} // POST: Function has determined if the progressive square can be formed and outputs result accordingly.