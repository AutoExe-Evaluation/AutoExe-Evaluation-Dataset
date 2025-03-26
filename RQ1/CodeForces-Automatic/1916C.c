#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100000); // PRE: 1 <= n <= 10^5
        
        int v[n];
        for(int i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }
        
        int odd = 0, sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += v[i];
            odd += (v[i] & 1);
            if(i == 0) {
                printf("%lld ", sum);
            } else {
                printf("%lld ", sum - (odd / 3) - (odd % 3 == 1));
            }
        }
        printf("\n");
        assert(sum - (odd / 3) - (odd % 3 == 1) >= 0); // POST: final result is non-negative
    }
    return 0;
}