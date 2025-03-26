#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp(const int *a, const int *b) {
    return (*a - *b);
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 9); // PRE: 1 <= n <= 9
        int *v = (int *)malloc(n * sizeof(int));
        
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 0 && v[i] <= 9); // PRE: 0 <= a_i <= 9
        }

        qsort(v, n, sizeof(int), (int(*)(const void*, const void*))cmp);
        v[0]++;
        int pro = 1;
        for (int i = 0; i < n; i++) {
            pro = pro * v[i];
        }
        
        printf("%d\n", pro);
        assert(pro >= 1); // POST: product should be at least 1 after incrementing a digit
        free(v);
    }
    return 0;
}