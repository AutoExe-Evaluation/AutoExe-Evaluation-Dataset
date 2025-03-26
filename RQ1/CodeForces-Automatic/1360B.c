#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: number of test cases must be in the range [1, 1000]

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 50); // PRE: number of athletes must be in the range [2, 50]
        
        int* v = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000); // PRE: athlete's strength must be in the range [1, 1000]
        }

        // Sort the array using bubble sort
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (v[j] > v[j + 1]) {
                    int temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }

        int diff = __INT_MAX__;
        for (int i = 1; i < n; i++) {
            diff = MIN(v[i] - v[i - 1], diff);
        }
        printf("%d\n", diff);
        assert(diff >= 0); // POST: the computed minimum difference must be non-negative

        free(v);
    }
    
    return 0;
}