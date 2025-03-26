#include <stdio.h>
#include <assert.h>

typedef long long ll;

ll points(ll r) {
    ll p = 0;
    for (ll x = 0; x <= r; ++x) {
        ll y, d = (r + 1) * (r + 1) - x * x;
        ll l = 0, h = r;
        while (l <= h) {
            ll mid = l + (h - l) / 2;
            if (mid * mid < d) {
                y = mid;
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        }
        if (x == 0) {
            p += (y * 2 + 1);
        } else {
            p += ((y * 2 + 1) * 2);
        }
    }
    return p;
}

int main() {
    int TCS;
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 ≤ t ≤ 1000
    scanf("%d", &TCS);
    ll total_r = 0; // to check the assert sum condition
    for (int TC = 1; TC <= TCS; ++TC) {
        ll r;
        scanf("%lld", &r);
        assert(r >= 1 && r <= 100000); // PRE: 1 ≤ r ≤ 10^5
        total_r += r; // accumulating r for postcondition
        ll p1 = points(r);
        ll p2 = points(r - 1);
        printf("%lld\n", p1 - p2);
    }
    assert(total_r <= 100000); // POST: The sum of r over all test cases does not exceed 10^5
    return 0;
}