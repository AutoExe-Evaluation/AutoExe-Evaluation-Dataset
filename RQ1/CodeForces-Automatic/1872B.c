#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;
#define nl '\n'

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= t <= 1000
    
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 100); // PRE: 1 <= n <= 100
        
        int traps[100][2]; // array to store traps
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &traps[i][0], &traps[i][1]);
            assert(traps[i][0] >= 1 && traps[i][0] <= 200); // PRE: 1 <= d_i <= 200
            assert(traps[i][1] >= 1 && traps[i][1] <= 200); // PRE: 1 <= s_i <= 200
            if (traps[i][1] % 2 == 0) {
                traps[i][1]--;
            }
            traps[i][0] += traps[i][1] / 2; // adjust room number
        }

        int max_k = traps[0][0];
        for (int i = 1; i < n; i++) {
            if (traps[i][0] < max_k) {
                max_k = traps[i][0];
            }
        }

        assert(max_k >= 1); // POST: max_k should be at least 1
        printf("%d%s", max_k, nl);
    }
    
    return 0;
}