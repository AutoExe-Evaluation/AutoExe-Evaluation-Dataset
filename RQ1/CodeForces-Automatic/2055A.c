#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define yn(f)  f? printf("YES\n"):printf("NO\n")

int main()
{
    long long TCS;
    scanf("%lld", &TCS);
    
    assert(TCS >= 1 && TCS <= 500); // PRE: Number of test cases should be in range

    for (long long TC = 1; TC <= TCS; ++TC)
    {
        long long n, a, b;
        scanf("%lld %lld %lld", &n, &a, &b);

        assert(n >= 2 && n <= 100); // PRE: Number of lilypads should be in range
        assert(a >= 1 && a <= n); // PRE: Alice's position should be valid
        assert(b >= 1 && b <= n); // PRE: Bob's position should be valid
        assert(a != b); // PRE: Alice and Bob must be on distinct lilypads

        yn(abs(a - b - 1) % 2);
    }

    return 0;
    
    // POST: Proper output is produced based on the positions of Alice and Bob
}