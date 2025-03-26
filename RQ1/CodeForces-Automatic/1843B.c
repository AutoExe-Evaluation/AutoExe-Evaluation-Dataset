#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases in the valid range
    
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: length of array in the valid range
        
        ll *v = (ll *)malloc(n * sizeof(ll));
        int size = 0;

        for (int i = 0; i < n; ++i) {
            ll x;
            scanf("%lld", &x);
            assert(x >= -1000000000LL && x <= 1000000000LL); // PRE: element within bounds
            if (x != 0) {
                v[size++] = x;
            }
        }
        
        ll sum = 0, ct = 0;
        int flag = 1;
        for (int i = 0; i < size; ++i) {
            ll x = v[i];
            if (x < 0 && flag) {
                ct++;
                flag = 0;
            } else if (x > 0) {
                flag = 1;
            }
            sum += llabs(x);
        }
        
        printf("%lld %lld\n", sum, ct);
        free(v);
        assert(sum >= 0); // POST: the sum is non-negative
    }
    return 0;
}