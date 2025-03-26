#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MOD 1000000007
#define N 300010

long long dp[N];

long long pow(long long x, long long y, long long m) {
    long long ans = 1;
    x %= m;
    while (y) {
        if (y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

int func(int n) {
    if (n == 0 || n == 1)
        return 1;
    if (dp[n] != -1) return dp[n];
    dp[n] = (func(n - 1) + (2LL * (n - 1) * func(n - 2)) % MOD) % MOD;
    return dp[n];
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases must be within bounds.
    
    while (TC--) {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(n >= 1 && n <= 300000); // PRE: Size of the chessboard must be within bounds.
        assert(k >= 0 && k <= n); // PRE: Number of moves must be within valid range.
        
        memset(dp, -1, sizeof(dp));
        int used = 0;
        for (int i = 0; i < k; ++i) {
            int r, c;
            scanf("%d %d", &r, &c);
            assert(r >= 1 && r <= n && c >= 1 && c <= n); // PRE: Move coordinates must be valid.
            used += 2 - (r == c);
        }
        int m = n - used;
        int ans = func(m);
        printf("%d\n", ans);
        assert(ans >= 0); // POST: The answer must be non-negative as per problem constraints.
    }
    return 0;
}