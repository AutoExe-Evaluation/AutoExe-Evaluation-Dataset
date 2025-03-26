#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be within valid range

    for (int TC = 1; TC <= TCS; ++TC) {
        int x, y;
        scanf("%d %d", &x, &y);
        
        assert(x >= 0 && y >= 0 && x != y); // PRE: x and y must be non-negative and distinct
        
        int ans = 0;
        while (1) {
            if ((x ^ y) & 1) break;
            ans++;
            x >>= 1;
            y >>= 1;
        }
        
        int result = 1 << ans;
        printf("%d\n", result);
        assert(result > 0); // POST: The result should be a positive integer since x and y are distinct and non-negative
    }
    return 0;
}