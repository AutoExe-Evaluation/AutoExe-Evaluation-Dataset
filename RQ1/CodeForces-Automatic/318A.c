#include <stdio.h>
#include <assert.h>

#define ll long long

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    
    assert(n >= 1 && k >= 1 && k <= n); // PRE: 1 ≤ k ≤ n ≤ 10^12
    
    ll result;
    if (k <= n / 2)
        result = 2 * k - 1;
    else {
        if (n & 1) {
            if (k == n / 2 + 1)
                result = n;
            else
                result = 2 * (k - n / 2 - 1);
        } else
            result = 2 * (k - n / 2);
    }
    
    printf("%lld\n", result);
    
    assert(result >= 1 && result <= n); // POST: Output number is in the range of 1 to n
    return 0;
}