#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: Number of test cases must be between 1 and 500
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 100); // PRE: Length of array must be between 2 and 100
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: Elements must be within the given range
        }

        qsort(v, n, sizeof(int), compare);
        
        if (v[0] % v[n - 1] == 0) {
            printf("-1\n");
            free(v);
            continue;
        }
        
        int ct = 0;
        for (int i = 0; i < n - 1; i++) {
            if (v[i] == v[n - 1])
                break;
            ct++;
        }
        
        printf("%d %d\n", ct, n - ct);
        for (int i = 0; i < ct; i++)
            printf("%d ", v[i]);
        printf("\n");
        for (int i = ct; i < n; i++)
            printf("%d ", v[i]);
        printf("\n");
        
        free(v);
    }
    return 0;
} // POST: The outputs b and c satisfy l_b >= 1, l_c >= 1 and c_j is not a divisor of b_i for all valid i, j.