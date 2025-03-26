#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    
    assert(TC > 0 && TC <= 100); // PRE: Number of test cases should be within the bounds
    
    while (TC--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        
        assert(n > 0 && n <= 100); // PRE: n should be within bounds
        assert(m > 0 && m <= 100); // PRE: m should be within bounds
        assert(k > 0 && k <= 100); // PRE: k should be within bounds
        
        int x, y;
        scanf("%d %d", &x, &y);
        
        assert(x > 0 && x <= n); // PRE: x should be within room bounds
        assert(y > 0 && y <= m); // PRE: y should be within room bounds
        
        int vika_color = (x + y) % 2;
        int caught = 0;
        
        for (int i = 0; i < k; i++) {
            int p, q;
            scanf("%d %d", &p, &q);
            
            assert(p > 0 && p <= n); // PRE: p should be within room bounds
            assert(q > 0 && q <= m); // PRE: q should be within room bounds
            
            int friend_color = (p + q) % 2;
            if (vika_color == friend_color) {
                caught = 1;
            }
        }
        
        if (caught) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
    
    // POST: If no friend has the same "color" as Vika, it is possible for her to run away
    assert(caught == 0 || caught == 1); // Ensures caught variable is valid
    
    return 0;
}