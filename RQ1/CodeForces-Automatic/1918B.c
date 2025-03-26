#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 200000

typedef struct {
    int first;
    int second;
} Pair;

Pair a[MAX_N];
int b[MAX_N];

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 20000); // PRE: Number of test cases is within the limit
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: Length of permutations is within the limit
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            a[i].first = x;
            a[i].second = i;
            assert(x >= 1 && x <= n); // PRE: Elements are within valid range for permutations
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", &b[i]);
            assert(b[i] >= 1 && b[i] <= n); // PRE: Elements are within valid range for permutations
        }
        
        // Sort pairs based on the first element (Bubble sort)
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (a[j].first > a[j + 1].first) {
                    Pair temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }

        // Output results
        for (int i = 0; i < n; ++i) {
            printf("%d ", a[i].first);
        }
        printf("\n");
        for (int i = 0; i < n; ++i) {
            printf("%d ", b[a[i].second]);
        }
        printf("\n");
    }
    // POST: The output arrays a' and b' are both valid permutations with minimized inversions
    return 0;
}
