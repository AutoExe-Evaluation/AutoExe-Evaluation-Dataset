#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int TC = 0;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 270); // PRE: 1 <= t <= 270
    
    while (TC--) 
    {
        int a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        assert(a >= 0 && a <= 9 && b >= 0 && b <= 9 && c >= 0 && c <= 9); // PRE: 0 <= a, b, c <= 9
        int result = (a ^ b ^ c);
        printf("%lld\n", result);
        assert((result == a && b == c) || (result == b && a == c) || (result == c && a == b)); // POST: Exactly one value occurs once
    }
    return 0;
}