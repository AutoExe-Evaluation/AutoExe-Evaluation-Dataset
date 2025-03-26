#include <stdio.h>
#include <assert.h>

#define ll long long

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10000

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 100000
        
        ll sum = 0;
        int ct = 0;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: 1 ≤ a_i ≤ 10^9
            if (x == 1)
                ct++;
            sum += x;
        }
        
        if (sum >= ct + n && n > 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        assert((sum >= ct + n && n > 1) ? (printf("YES\n")) : (printf("NO\n"))); // POST: condition for a good array
    }
    
    return 0;
}