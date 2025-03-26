#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4
    
    while (TC--) {
        int a, b, c, d;
        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        
        assert(-100000000 <= a && a <= 100000000); // PRE: -10^8 <= a <= 10^8
        assert(-100000000 <= b && b <= 100000000); // PRE: -10^8 <= b <= 10^8
        assert(-100000000 <= c && c <= 100000000); // PRE: -10^8 <= c <= 10^8
        assert(-100000000 <= d && d <= 100000000); // PRE: -10^8 <= d <= 10^8
        
        if (b > d || c - a > d - b) {
            printf("-1\n");
        } else {
            int moves = 2 * (d - b) + a - c;
            printf("%lld\n", moves);
            assert(moves >= 0); // POST: The calculated moves are non-negative
        }
    }
    return 0;
}