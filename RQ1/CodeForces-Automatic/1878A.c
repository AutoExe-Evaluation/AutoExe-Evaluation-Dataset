#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be in range [1, 1000]

    while (TC--) {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(n >= 1 && n <= 100); // PRE: Size of array should be in range [1, 100]
        assert(k >= 1 && k <= 100); // PRE: k should be in range [1, 100]

        int v[100];
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 100); // PRE: Elements of array should be in range [1, 100]
        }

        int count_k = 0; // Count occurrences of k
        int max_other = 0; // Count occurrences of others
        for (int i = 0; i < n; ++i) {
            if (v[i] == k) {
                count_k++;
            } else {
                max_other++; // Count any other integer
            }
        }

        if (count_k > max_other) {
            printf("YES\n");
            assert(count_k > max_other); // POST: k is the most common element
        } else {
            printf("NO\n");
            assert(count_k <= max_other); // POST: k is not the most common element
        }
    }
    return 0;
}