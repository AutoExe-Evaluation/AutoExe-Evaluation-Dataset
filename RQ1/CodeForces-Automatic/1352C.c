#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 1000); // PRE: 1 ≤ t ≤ 1000
    
    while (t--) {
        int n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 2 && n <= 1000000000); // PRE: 2 ≤ n ≤ 10^9
        assert(k >= 1 && k <= 1000000000); // PRE: 1 ≤ k ≤ 10^9
        
        int L = 1, R = 5000000007, ans = -1;
        while (L <= R) {
            int mid = L + (R - L) / 2;
            if (mid % n == 0) mid++;
            int pos = mid - mid / n;
            if (pos < k)
                L = mid + 1;
            else if (pos > k)
                R = mid - 1;
            else {
                ans = mid;
                break;
            }
        }
        assert(ans != -1); // POST: ans should be found
        printf("%lld\n", ans);
    }
    return 0;
}