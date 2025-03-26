#include <stdio.h>
#include <assert.h>

#define MAX_N 200000

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

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4
    
    while (TCS--) {
        long long h, n;
        scanf("%lld %lld", &h, &n);
        assert(h >= 1 && h <= 200000); // PRE: 1 <= h <= 2 * 10^5
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        
        int a[MAX_N], b[MAX_N];
        long long initial_health = h;

        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            h -= a[i];
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", &b[i]);
        }

        if (h <= 0) {
            printf("1\n");
            assert(initial_health <= 0); // POST: health less than or equal to 0 in one turn
            continue;
        }

        long long l = 0, r = initial_health * 200000, ans;
        while (l <= r) {
            long long mid = l + (r - l) / 2;
            long long s = 0;

            for (int i = 0; i < n; ++i) {
                s += (mid / b[i]) * a[i];
            }

            if (initial_health - s <= 0) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        printf("%lld\n", ans + 1);
        assert(h - (initial_health - (ans + 1) * (n ? a[0] / b[0] : 0)) <= 0); // POST: health is reduced to 0 or below after the calculated turns
    }
    return 0;
}