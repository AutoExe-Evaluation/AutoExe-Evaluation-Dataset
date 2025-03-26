#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100); // PRE: 1 ≤ n ≤ 100
    int *arr = (int *)malloc(n * sizeof(int));
    int *unique = (int *)malloc(101 * sizeof(int));
    for (int i = 0; i < 101; i++) unique[i] = 0;

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
        assert(arr[i] >= -100 && arr[i] <= 100); // PRE: elements are within the range [-100, 100]
        unique[arr[i] + 100] = 1;  // Shift to handle negative indices
    }

    int first = -1, second = -1;
    for (int i = 0; i < 101; ++i) {
        if (unique[i]) {
            if (first == -1) {
                first = i - 100;
            } else if (second == -1) {
                second = i - 100;
                break;
            }
        }
    }
    
    if (second == -1) {
        printf("NO\n");
        assert(second == -1); // POST: if no second order statistics, output "NO"
    } else {
        printf("%d\n", second);
        assert(second > first); // POST: the second order statistic is greater than the first
    }

    free(arr);
    free(unique);
    return 0;
}