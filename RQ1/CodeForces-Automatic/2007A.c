#include <stdio.h>
#include <assert.h>

long long pow(long long x, long long y, long long m) {
    long long ans = 1; 
    x %= m; 
    while (y) { 
        if (y & 1) 
            ans = (ans * x) % m; 
        x = (x * x) % m; 
        y >>= 1; 
    } 
    return ans; 
}

int main() {
    int TCS; 
    scanf("%d", &TCS); 
    assert(TCS >= 1 && TCS <= 500); // PRE: 1 <= t <= 500

    while (TCS--) {
        int l, r; 
        scanf("%d %d", &l, &r); 
        assert(l >= 1 && r <= 1000 && l <= r); // PRE: 1 <= l <= r <= 1000

        int ct = 0; 
        for (int i = l; i <= r - 2; ++i) {
            if (i & 1) {
                ct++; 
                i += 3; 
            }
        }
        printf("%d\n", ct);
        assert(ct >= 0); // POST: Maximum operations can't be negative
    }
    return 0; 
}