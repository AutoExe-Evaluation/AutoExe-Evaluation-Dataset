#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 200); // PRE: number of test cases t is within the range [1, 200]

    while (t--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 1000); // PRE: length of array a n is within the range [2, 1000]
        
        int m = n * (n - 1) / 2;
        int *mp = (int *)calloc(2000002, sizeof(int));
        int *v = (int *)malloc(m * sizeof(int));
        
        for (int i = 0; i < m; ++i) {
            int x;
            scanf("%lld", &x);
            assert(x >= -1000000000 && x <= 1000000000); // PRE: elements of array b are within range [-10^9, 10^9]
            mp[x]++;
        }
        
        int index = 0;
        for (int i = -1000000000; i <= 1000000000; i++) {
            while (mp[i] > 0) {
                v[index++] = i;
                mp[i] -= n - index;
            }
        }

        for (int i = 0; i < n; i++) {
            printf("%lld ", v[i]);
        }
        printf("%lld\n", (int)1e9);
        free(mp);
        free(v);
    }
    
    // POST: The output array a is constructed correctly from b
    return 0;
}