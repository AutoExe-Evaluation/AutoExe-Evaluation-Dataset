#include <stdio.h>
#include <assert.h>

#define ll long long

int main()
{
    int TC;
    scanf("%d", &TC);
    
    assert(TC >= 1 && TC <= 100000); // PRE: Number of test cases should be in the range [1, 10^5]
    
    while (TC--) {
        ll n;
        scanf("%lld", &n);
        
        assert(n >= 4); // PRE: Size of the cinnabon roll should be >= 4
        
        ll chocolate_length = n * (n + 1) + n + 2;
        printf("%lld\n", chocolate_length);
        
        assert(chocolate_length == n * (n + 1) + n + 2); // POST: The computed chocolate length is correct
    }
    return 0;
}