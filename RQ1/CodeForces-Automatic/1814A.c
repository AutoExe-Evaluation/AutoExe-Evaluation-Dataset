#include <stdio.h>
#include <assert.h>

// Short forms
typedef long long ll;

// Outputs
#define yes printf("YES\n")
#define no printf("NO\n")

int main()
{
    int TC = 1;
    scanf("%d", &TC);
    
    // PRE: 1 <= t <= 10000
    assert(TC >= 1 && TC <= 10000);
    
    while (TC--) {
        ll n, k;
        scanf("%lld %lld", &n, &k);
        
        // PRE: 1 <= k <= n <= 10^18 AND k != 2
        assert(k >= 1 && k <= n && n <= 1000000000000000000LL && k != 2);

        if (!(n & 1))
            yes;
        else if (n & 1 && k & 1)
            yes;
        else
            no;
        
        // POST: "YES" is printed if 2*x + k*y = n is possible for non-negative x, y
        // When n is even or when n is odd and k is odd, the representation is possible.
        assert(((!(n & 1) || (n & 1 && (k & 1))))); // A simple check satisfies the condition
    }
    return 0;
}