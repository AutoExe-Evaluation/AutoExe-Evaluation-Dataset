#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within the constraints
    while(TCS--) {
        int n, x;
        scanf("%lld %lld", &n, &x);
        
        assert(n >= 1 && n <= 500000); // PRE: Number of car models is within the constraints
        assert(x >= 1 && x <= 10); // PRE: Maximum number of cars per customer is within the constraints
        
        int mx = 0, sum = 0;
        
        for(int i = 0; i < n; ++i) {
            int c;
            scanf("%lld", &c);
            assert(c >= 1 && c <= 1000000000); // PRE: Number of cars per model is within constraints
            sum += c;
            if(c > mx) {
                mx = c;
            }
        }
        
        int result = mx > (sum + x - 1) / x ? mx : (sum + x - 1) / x;
        printf("%lld\n", result);
        
        assert(result >= 1); // POST: The result should be at least 1 customer
    }
    return 0;
}