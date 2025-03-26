#include <stdio.h>
#include <assert.h>

#define MAXN 101

unsigned long long mypow(unsigned long long a, unsigned long long b, unsigned long long m) {
    unsigned long long ans = 1;
    a %= m;
    while (b) {
        if (b & 1) ans = (ans * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return ans;
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: 1 ≤ t ≤ 100
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 100); // PRE: 1 ≤ n ≤ 100
        int m[101] = {0};
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= 100); // PRE: 1 ≤ a_i ≤ 100
            m[x]++;
        }
        int ans = 0;
        for (int i = 1; i <= 100; ++i)
            ans += m[i] / 3;
        printf("%d\n", ans);
        assert(ans >= 0); // POST: max number of polygons is non-negative
    }
    return 0;
}