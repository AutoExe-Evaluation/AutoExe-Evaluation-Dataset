#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases must be in range [1, 100]
    
    while (TC--) {
        long long x, y, k;
        scanf("%lld %lld %lld", &x, &y, &k);
        assert(x >= 1 && x <= 100 && y >= 1 && y <= 100 && x != y); // PRE: x, y must be in range [1, 100] and x != y
        assert(k >= 0 && k <= 100); // PRE: k must be in range [0, 100]
        
        long long result;
        if (x >= y) {
            result = x;
        } else if (x + k >= y) {
            result = y;
        } else {
            result = y + y - x - k;
        }
        
        printf("%lld\n", result);
        assert(result >= 1); // POST: The result must always be a positive time
    }
    return 0;
}