#include <stdio.h>
#include <assert.h>

#define ll long long

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 ≤ t ≤ 1000
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 50); // PRE: 2 ≤ n ≤ 50
        
        int sum = 0;
        int hasOdd = 0, hasEven = 0;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= 50); // PRE: 1 ≤ a_i ≤ 50
            
            sum += x;
            if (x % 2 == 0) hasEven = 1;
            else hasOdd = 1;
        }
        
        assert(hasOdd || hasEven); // PRE: at least one element must exist

        if ((hasOdd && hasEven) || (sum % 2 == 0 && (hasOdd || hasEven))) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        
        assert((hasOdd && hasEven) || (sum % 2 == 0 && (hasOdd || hasEven))); // POST: valid partitioning satisfies color sums
    }
    return 0;
}