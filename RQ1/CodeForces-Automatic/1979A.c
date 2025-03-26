#include <stdio.h>
#include <limits.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within limits

    while(TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 50000); // PRE: Array size is within limits
        
        int v[n];
        for(int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: Array element is within limits
        }
        
        int mx = INT_MAX;
        for(int i = 1; i < n; ++i) {
            int x = v[i - 1];
            int y = v[i];
            mx = (mx < (x > y ? x : y)) ? mx : (x > y ? x : y);
        }
        
        printf("%d\n", mx - 1);
        assert(mx - 1 >= 0); // POST: Alice's maximum k guarantees she wins
    }
    
    return 0;
}