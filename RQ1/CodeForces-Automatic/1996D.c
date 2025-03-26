#include <stdio.h>
#include <assert.h>

#define int long long

int count_triplets(int n, int x) {
    int ct = 0;
    for (int a = 1; a <= x; ++a) {
        int y = (x - a < n / a) ? x - a : n / a;
        for (int b = 1; b <= y; ++b) {
            int c = (x - a - b < (n - a * b) / (a + b)) ? x - a - b : (n - a * b) / (a + b);
            ct += (c > 0) ? c : 0;
        }
    }
    return ct;
}

signed main() {
    int TCS = 0;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be between 1 and 10^4

    while (TCS--) {
        int n, x;
        scanf("%lld %lld", &n, &x);
        assert(n >= 1 && n <= 1000000); // PRE: n should be between 1 and 10^6
        assert(x >= 1 && x <= 1000000); // PRE: x should be between 1 and 10^6
        
        int result = count_triplets(n, x);
        assert(result >= 0); // POST: Result should be non-negative
        printf("%lld\n", result);
    }
}