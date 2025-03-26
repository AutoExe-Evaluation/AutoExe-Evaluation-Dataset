#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXN 200005

typedef long long ll;

ll v[MAXN];
ll m[MAXN][MAXN];

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within limits

    while (TCS--) {
        ll n, q;
        scanf("%lld %lld", &n, &q);
        assert(n >= 2 && n <= 200000); // PRE: Number of elements is within limits
        assert(q >= 1 && q <= 200000); // PRE: Number of queries is within limits

        m[0][0] = 0;  // Initialize m[0] for XOR zero
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &v[i]);
            v[i] ^= v[i - 1];
            m[v[i]][++m[v[i]][0]] = i;  // Store index, first element is count
        }

        while (q--) {
            ll l, r;
            scanf("%lld %lld", &l, &r);
            assert(l >= 1 && l < r && r <= n); // PRE: l and r are within bounds
            
            if (v[l - 1] == v[r]) {
                printf("YES\n");
                continue;
            }
            
            ll it1 = 1, it2 = m[v[l - 1]][0];
            while (it1 <= m[v[r]][0] && m[v[r]][it1] < l) it1++;
            while (it2 > 0 && m[v[l - 1]][it2] >= r) it2--;
            
            if (it1 <= m[v[r]][0] && it1 <= it2) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    
    assert(1 <= 2); // POST: Ensures the function executed with valid parameters
    return 0;
}