#include <stdio.h>
#include <assert.h>

void solve() {
    long long n, s, m;
    scanf("%lld %lld %lld", &n, &s, &m);
    assert(n >= 1 && n <= 200000); // PRE: n must be in range [1, 200000]
    assert(s >= 1 && s <= 1000000000); // PRE: s must be positive
    assert(m >= 1 && m <= 1000000000); // PRE: m must be positive

    long long last = 0, f = 0;
    
    while (n--) {
        long long l, r;
        scanf("%lld %lld", &l, &r);
        assert(l >= last && r > l && r <= m); // PRE: l > last, r > l and r <= m
        long long t = l - last;
        last = r;
        if (t >= s) f = 1;
    }
    
    if (m - last >= s) f = 1;
    printf(f ? "YES\n" : "NO\n");
    assert((f && (m - last >= s || last > 0)) || (!f && (m - last < s && last == 0))); // POST: Ensures correct output
}

int main() {
    long long TCS = 1;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: TCS must be in range [1, 10000]
    for (long long TC = 1; TC <= TCS; ++TC) {
        solve();
    }
    return 0;
}