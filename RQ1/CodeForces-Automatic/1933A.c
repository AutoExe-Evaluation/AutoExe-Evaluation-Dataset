#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: number of test cases should be within bounds

    while (TC--) {
        int n, sum = 0;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: number of elements should be within bounds
        
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            assert(x >= -100 && x <= 100); // PRE: each element should be within bounds
            sum += abs(x);
        }
        
        printf("%d\n", sum);
        assert(sum >= 0); // POST: the maximum sum cannot be negative
    }
    
    return 0;
}