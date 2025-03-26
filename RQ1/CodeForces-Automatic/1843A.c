#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int t;
    scanf("%d", &t);
    
    assert(t >= 1 && t <= 1000); // PRE: Number of test cases must be between 1 and 1000.
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        assert(n >= 1 && n <= 50); // PRE: Length of array must be between 1 and 50.
        
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 50); // PRE: Each element of array must be between 1 and 50.
        }
        
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (v[j] > v[j + 1]) {
                    int temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
        
        int cost = 0;
        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            cost += v[j] - v[i];
        }

        assert(cost >= 0); // POST: Cost must always be non-negative.
        printf("%d\n", cost);
        
        free(v);
    }
    return 0;
}