#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int compare(const int *a, const int *b) {
    return (*a - *b);
}

int main() {
    int TC = 0;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases should be within limits

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: Length of the array should be within limits

        int *v = (int *)malloc(n * sizeof(int));
        for(int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: Elements of the array must be within limits
        }
        
        int *v2 = (int *)malloc(n * sizeof(int));
        for(int i = 0; i < n; ++i) v2[i] = v[i];
        
        qsort(v2, n, sizeof(int), (int(*)(const void *, const void *))compare);
        
        int possible = 1;
        for(int i = 0; i < n; ++i) {
            if(v[i] % 2 == 0 && v2[i] % 2 != 0) {
                possible = 0;
                break;
            } else if (v[i] % 2 != 0 && v2[i] % 2 == 0) {
                possible = 0;
                break;
            }
        }
        
        if(possible)
            printf("YES\n");
        else
            printf("NO\n");

        free(v);
        free(v2);
    }
    // POST: The output is correct based on the ability to sort
    return 0;
}