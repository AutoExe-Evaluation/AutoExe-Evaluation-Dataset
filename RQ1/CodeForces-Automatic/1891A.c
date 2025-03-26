#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4
    
    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 20); // PRE: 1 ≤ n ≤ 20
        
        int v[20];
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 0 && v[i] <= 1000); // PRE: 0 ≤ a_i ≤ 1000
        }
        
        for (int i = 3; i < n; ++i) {
            if (v[i] < v[i - 1] && (i & (i - 1))) {
                printf("NO\n");
                assert(0); // POST: array cannot be sorted
                return 0;
            }
        }
        printf("YES\n");
        assert(1); // POST: array can be sorted
    }
    return 0;
}