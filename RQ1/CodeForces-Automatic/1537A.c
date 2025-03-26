#include <stdio.h>
#include <assert.h>

int main() {
    int TCS = 0;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases t is between 1 and 1000
    
    while (TCS--) {
        int n = 0;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: Length of the array n is between 1 and 50
        
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            int x = 0;
            scanf("%d", &x);
            assert(x >= -10000 && x <= 10000); // PRE: Each element a_i is between -10^4 and 10^4
            sum += x; 
        }
        
        int result;
        if (n == sum) {
            result = 0;
        } else if (n > sum) {
            result = 1;
        } else {
            result = sum - n;
        }
        
        printf("%d\n", result);
        assert(result >= 0); // POST: Minimum number of operations is non-negative
    }
    return 0;
}