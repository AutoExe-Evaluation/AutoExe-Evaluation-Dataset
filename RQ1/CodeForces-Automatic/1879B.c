#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 300000); // PRE: 1 <= n <= 3 * 10^5

        int *a = (int*)malloc(n * sizeof(int));
        int *b = (int*)malloc(n * sizeof(int));
        
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }
        
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: 1 <= b_i <= 10^9
        }

        // Sort a
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    int temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }

        // Sort b
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (b[j] > b[j + 1]) {
                    int temp = b[j];
                    b[j] = b[j + 1];
                    b[j + 1] = temp;
                }
            }
        }

        int row = 0, col = 0;
        for (int i = 0; i < n; ++i)
            row += a[i] + b[0];

        for (int i = 0; i < n; ++i)
            col += b[i] + a[0];

        printf("%lld\n", row < col ? row : col);

        free(a);
        free(b);
    }
    return 0; 
    // POST: The minimum possible total cost is computed for each test case
}