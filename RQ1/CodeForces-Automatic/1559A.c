#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases is within bounds
    while (TCS--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100); // PRE: Length of sequence is within bounds
        int v[100];
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 0 && v[i] <= 1000000000); // PRE: Elements are within bounds
        }
        int ans = v[0];
        for (int i = 1; i < n; ++i) {
            ans &= v[i];
        }
        printf("%lld\n", ans);
        assert(ans >= 0 && ans <= 1000000000); // POST: Result is within bounds [0, 10^9]
    }
    return 0;
}