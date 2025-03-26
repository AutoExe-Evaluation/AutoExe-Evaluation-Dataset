#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 1000000000); // PRE: 1 ≤ n ≤ 10^9

        if (n & 1)
            n++;
        
        int result = n / 2;
        printf("%lld\n", result);
        assert(result >= 0 && result <= 5000000000); // POST: Maximum side length of square
    }
    return 0;
}