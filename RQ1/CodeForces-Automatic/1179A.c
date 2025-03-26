#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

ll power(ll x, ll y, ll m) {
    ll ans = 1;
    x %= m;
    while (y) {
        if (y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

int main() {
    ll n, q;
    scanf("%lld %lld", &n, &q);
    
    ll *d = (ll *)malloc(n * sizeof(ll));
    ll mx = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &d[i]);
        if (d[i] > mx) mx = d[i];
    }
    
    ll *pairsA = (ll *)malloc(n * sizeof(ll));
    ll *pairsB = (ll *)malloc(n * sizeof(ll));
    int pair_count = 0;

    int front = 0, back = n;
    
    while (d[front] != mx) {
        ll a = d[front++];
        ll b = d[front++];
        pairsA[pair_count] = a;
        pairsB[pair_count] = b;
        pair_count++;

        if (a > b) {
            d[--front] = a;
            d[back++] = b;
        } else {
            d[--front] = b;
            d[back++] = a;
        }
    }
    
    ll *cycle = (ll *)malloc((back - front - 1) * sizeof(ll));
    int cycle_size = 0;
    for (int i = front + 1; i < back; ++i) {
        cycle[cycle_size++] = d[i];
    }

    // Assert PRE: There must be at least one operation to perform
    assert(q >= 0); // PRE: Number of queries must be non-negative

    while (q--) {
        ll m;
        scanf("%lld", &m);
        // Assert PRE: m should be greater than 0
        assert(m > 0);
        
        if (m <= pair_count) {
            printf("%lld %lld\n", pairsA[m - 1], pairsB[m - 1]);
            // Assert POST: Correct elements are printed from pairsA and pairsB
            assert(pairsA[m - 1] > 0 || pairsB[m - 1] > 0); // POST: Valid outputs
        } else {
            m -= pair_count;
            ll k = cycle[(m - 1) % cycle_size];
            printf("%lld %lld\n", mx, k);
            // Assert POST: Valid output with a known maximum
            assert(mx >= 0 && k >= 0); // POST: Valid values for A and B
        }
    }

    free(d);
    free(pairsA);
    free(pairsB);
    free(cycle);
    
    return 0;
}