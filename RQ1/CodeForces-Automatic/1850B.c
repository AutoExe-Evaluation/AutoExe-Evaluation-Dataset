#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: 1 <= t <= 100
    
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: 1 <= n <= 50
        
        int max_quality = 0, winner_index = 0;
        
        for (int i = 1; i <= n; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            assert(x >= 1 && x <= 50); // PRE: 1 <= a_i <= 50
            assert(y >= 1 && y <= 50); // PRE: 1 <= b_i <= 50
            
            if (x <= 10) {
                if (y > max_quality) {
                    max_quality = y;
                    winner_index = i;
                }
            }
        }
        assert(winner_index > 0); // POST: There is a winner with index > 0
        printf("%d\n", winner_index);
    }
    
    return 0;
}