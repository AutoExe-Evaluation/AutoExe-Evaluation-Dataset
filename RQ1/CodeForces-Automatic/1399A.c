#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 50

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases is within the given limits

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: Length of the array is within the given limits

        int v[MAX_N];
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] > 0 && v[i] <= 100); // PRE: Each element is a positive integer within the limits
        }

        if (n == 1) {
            printf("YES\n");
            assert(1 == 1); // POST: If the array has one element, it's always possible
            continue;
        }

        // Sort the array
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (v[i] > v[j]) {
                    int temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;
                }
            }
        }

        // Check if all elements can be reduced to one element
        for (int i = 1; i < n; i++) {
            if (v[i] - v[i - 1] > 1) {
                printf("NO\n");
                assert(v[i] - v[i - 1] > 1); // POST: If the difference is greater than 1, it's not possible
                break;
            }
            if (i == n - 1) {
                printf("YES\n");
                assert(v[n-1] - v[0] <= 1); // POST: If we reach here, all elements can be reduced to one
            }
        }
    }
    return 0;
}