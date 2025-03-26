#include <stdio.h>
#include <assert.h>

int main() {
    long long n, s, ct = 0;
    scanf("%lld %lld", &n, &s);
    
    assert(n >= 1 && n <= 1000); // PRE: n should be in the range [1, 1000]
    assert(s >= 0 && s <= 1000000000); // PRE: s should be in the range [0, 10^9]

    for (long long i = 0; i < n; i++) {
        char c;
        long long x;
        scanf(" %c %lld", &c, &x);
        
        assert(x >= 1 && x <= 1000000000); // PRE: x should be in the range [1, 10^9]

        if (c == '+') {
            s += x;
        } else {
            if (x > s) {
                ct++;
            } else {
                s -= x;
            }
        }
    }
    
    assert(s >= 0); // POST: s should be non-negative
    printf("%lld %lld\n", s, ct);
    return 0;
}