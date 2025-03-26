#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: 1 <= t <= 500

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 100); // PRE: 2 <= n <= 100
        
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (v[j] > v[j + 1]) {
                    int temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
        
        int max_beauty = v[n - 1] - v[0];
        printf("%lld\n", max_beauty);
        free(v);
        assert(max_beauty >= 0); // POST: max_beauty >= 0 as elements are positive integers
    }
    
    return 0;
}