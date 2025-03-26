#include <stdio.h>
#include <assert.h>

#define YES printf("YES\n")
#define NO printf("NO\n")

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases must be within range

    while (TC--) {
        long long a, b;
        scanf("%lld%lld", &a, &b);
        assert(a >= 1 && a <= 1000000000); // PRE: a must be within range
        assert(b >= 1 && b <= 1000000000); // PRE: b must be within range
        
        if (a % 2 == 0 && a / 2 != b)
            YES;
        else if (b % 2 == 0 && b / 2 != a)
            YES;
        else
            NO;

        // POST: The output is "YES" if another rectangle can be formed; otherwise "NO".
    }
    
    return 0;
}