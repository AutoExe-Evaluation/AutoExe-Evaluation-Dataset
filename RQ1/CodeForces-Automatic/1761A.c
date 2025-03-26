#include <stdio.h>
#include <assert.h>

#define YES printf("YES\n");
#define NO printf("NO\n");

int main() {
    int TC, n, a, b;
    scanf("%d", &TC);
    
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is between 1 and 10^4

    while (TC--) {
        scanf("%d %d %d", &n, &a, &b);
        
        assert(n >= 1 && n <= 100); // PRE: n is between 1 and 100
        assert(a >= 1 && a <= n); // PRE: a is between 1 and n
        assert(b >= 1 && b <= n); // PRE: b is between 1 and n
        
        if (n == a && n == b)
            YES;
        else if (a + b < n - 1)
            YES;
        else
            NO;

        // POST: Output is "YES" if valid permutations exist; otherwise "NO"
    }
    return 0;
}