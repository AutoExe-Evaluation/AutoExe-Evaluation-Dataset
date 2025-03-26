#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: 1 <= t <= 100

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 500); // PRE: 2 <= n <= 500
        
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }

        int sorted = 1;
        for (int i = 1; i < n; ++i) {
            if (v[i] < v[i - 1]) {
                sorted = 0;
                break;
            }
        }

        if (!sorted) {
            printf("0\n");
        } else {
            int d = INT_MAX;
            for (int i = 1; i < n; ++i) {
                int r = v[i] - v[i - 1];
                if (r < d) {
                    d = r;
                }
            }
            int ans = (d / 2) + 1;
            printf("%d\n", ans); 
            assert(ans > 0); // POST: output is the minimum operations needed to make the array not sorted
        }

        free(v);
    }
    
    return 0;
}