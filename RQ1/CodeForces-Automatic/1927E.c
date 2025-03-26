#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 10000); // PRE: 1 <= t <= 10^4
    
    while (t--) {
        int n, k;
        scanf("%lld %lld", &n, &k);
        assert(k <= n && k >= 2 && k % 2 == 0); // PRE: 2 <= k <= n, k is even
        int l = 1, h = n;
        int v[n];
        
        for (int i = 0; i < k; ++i) {
            for (int j = i; j < n; j += k) {
                if (i & 1) v[j] = h--;
                else v[j] = l++;
            }
        }
        
        for (int i = 0; i < n; ++i)
            printf("%lld ", v[i]);
        printf("\n");
        
        // POST: max(s) - min(s) <= 1 condition is satisfied
        assert(1 <= v[0] && v[0] <= n); // Ensuring valid permutation property
    }
    return 0;
}