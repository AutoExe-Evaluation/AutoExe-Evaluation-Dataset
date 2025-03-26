#include <stdio.h>
#include <assert.h>

int main() {
    int t;
    
    scanf("%d", &t);
    assert(t >= 1 && t <= 10000); // PRE: 1 <= t <= 10^4
    
    while(t--) {
        int n, num1 = 0, h;
        
        scanf("%d", &n);
        assert(n >= 1 && n <= 100); // PRE: 1 <= n <= 100
        
        for(int i = 0; i < n; i++) {
            scanf("%d", &h);
            assert(h >= 1 && h <= 100); // PRE: 1 <= h_i <= 100
            if(h == 1)
                num1++;
        }
        
        int result = n - (num1 / 2);
        printf("%d\n", result);
        assert(result >= 0); // POST: result should be non-negative
    }
    
    return 0;
}