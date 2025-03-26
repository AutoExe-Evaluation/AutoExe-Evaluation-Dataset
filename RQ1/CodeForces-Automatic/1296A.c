#include <stdio.h>
#include <assert.h>

int main() {
    long long TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 2000); // PRE: Number of test cases is within bounds
    while (TC--) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 2000); // PRE: Number of elements is within bounds
        long long odd = 0, even = 0;

        for (long long i = 0; i < n; i++) {
            long long x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 2000); // PRE: Element value is within bounds
            if (x & 1)
                odd++;
            else
                even++;
        }

        if (odd == 0)
            printf("NO\n");
        else if (even == 0 && n % 2 == 0)
            printf("NO\n");
        else
            printf("YES\n");
        
        assert(odd > 0 || (even == 0 && n % 2 == 0)); // POST: Conditions for odd sum
    }
    return 0;
}