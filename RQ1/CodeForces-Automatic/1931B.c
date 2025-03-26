#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases must be between 1 and 10^4

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Number of containers must be between 1 and 2 * 10^5
        
        int v[n], net = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 0 && v[i] <= 1000000000); // PRE: Amount in each container must be between 0 and 10^9
            net += v[i];
        }
        
        int x = net / n, r = 0;
        for(int i = 0; i < n; ++i) {
            if(r + v[i] < x) {
                printf("NO\n");
                assert(net % n == 0); // POST: The sum must be divisible by n if operation is not possible
                return 0;
            }
            r = v[i] + r - x;
        }
        printf("YES\n");
        assert(net % n == 0); // POST: The sum is divisible by n
    }
    return 0;
}