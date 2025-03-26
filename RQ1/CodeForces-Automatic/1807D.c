#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 10000); // PRE: 1 <= t <= 10^4

    while (t--) {
        int n, q;
        scanf("%lld %lld", &n, &q);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        assert(q >= 1 && q <= 200000); // PRE: 1 <= q <= 2 * 10^5
        
        int v[n + 1];
        v[0] = 0;
        int ct = 0;

        for (int i = 1; i <= n; ++i) {
            int x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: 1 <= a_i <= 10^9
            if (x & 1) ct++;
            v[i] = ct;
        }

        while (q--) {
            int l, r, k;
            scanf("%lld %lld %lld", &l, &r, &k);
            assert(l >= 1 && l <= r && r <= n); // PRE: 1 <= l <= r <= n
            assert(k >= 1 && k <= 1000000000); // PRE: 1 <= k <= 10^9
            
            int rm = v[r] - v[l - 1];
            int odd = ct - v[r] + v[l - 1];
            if (k & 1) odd += r - l + 1;

            // POST: The sum of the entire array becomes odd
            if (odd & 1) 
                printf("YES\n");
            else 
                printf("NO\n");
        }
    }
    return 0;
}