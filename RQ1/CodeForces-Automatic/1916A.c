#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    // PRE: TC must be positive and no greater than 100
    assert(TC > 0 && TC <= 100);
    
    while (TC--) {
        int n, k;
        scanf("%lld %lld", &n, &k);
        // PRE: n and k must be between 1 and 5
        assert(n >= 1 && n <= 5);
        assert(k >= 1 && k <= 5);
        
        int prod = 1;
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%lld", &x);
            // PRE: Each b_i must be between 1 and 2023
            assert(x >= 1 && x <= 2023);
            prod *= x;
        }
        
        if (2023 % prod) {
            printf("NO\n");
        } else {
            printf("YES\n");
            printf("%lld ", 2023 / prod);
            for (int i = 0; i < k - 1; ++i) {
                printf("1 ");
            }
            printf("\n");
        }
    }
    // POST: For each test, if the conditions are valid, the output must reflect the potential removed elements or indicate impossibility.
    assert(TC >= 0); // Ensures we processed all test cases
    return 0;
}