#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: 1 <= t <= 100
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 100); // PRE: 2 <= n <= 100
        int *str = (int *)malloc(n * sizeof(int));
        int *end = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &str[i], &end[i]);
            assert(str[i] >= 1 && str[i] <= 1000000000); // PRE: 1 <= s_i <= 10^9
            assert(end[i] >= 1 && end[i] <= 100); // PRE: 1 <= e_i <= 100
        }
        int canWin = 1;
        for (int i = 1; i < n; ++i) {
            if (str[i] >= str[0] && end[i] >= end[0]) {
                printf("-1\n");
                canWin = 0;
                break;
            }
        }
        if (canWin) {
            printf("%d\n", str[0]);
        }
        free(str);
        free(end);
    }
    return 0;
    // POST: The output guarantees that the first athlete can win or indicates winning is impossible.
}