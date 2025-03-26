#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long
#define yes printf("YES\n")
#define no printf("NO\n")

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= t <= 1000

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100); // PRE: 1 <= n <= 100
        char st[4] = {0}; 
        int possible = 1;

        for (int i = 0; i < n; ++i) {
            int p, q;
            scanf("%lld %lld", &p, &q);
            assert(p >= -100 && p <= 100); // PRE: -100 <= x_i <= 100
            assert(q >= -100 && q <= 100); // PRE: -100 <= y_i <= 100
            
            if (p > 0) st[0] = 1; // 'r'
            else if (p < 0) st[1] = 1; // 'l'
            if (q > 0) st[2] = 1; // 'u'
            else if (q < 0) st[3] = 1; // 'd'
            
            if (st[0] + st[1] + st[2] + st[3] == 4) {
                possible = 0;
            }
        }
        
        if (possible)
            yes;
        else
            no;    
        
        // POST: successfully determined if all points can be reached
        assert(possible == 1 || possible == 0); // POST: possible is 0 or 1
    }
    return 0;
}