#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 104); // PRE: Number of test cases must be within given limits.
    
    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Length of sequence b must be within given limits.

        int *v = (int *)malloc(2 * n * sizeof(int));
        int size = 0;

        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: Each element of sequence b must be within given limits.
            
            if (i && v[size - 1] > x) {
                v[size++] = 1;
            }
            v[size++] = x;
        }

        printf("%lld\n", size);
        for (int i = 0; i < size; ++i) {
            printf("%lld ", v[i]);
        }
        printf("\n");

        free(v);
        assert(size <= 2 * n); // POST: Length of sequence a must not exceed 2*n.
    }

    return 0;
}