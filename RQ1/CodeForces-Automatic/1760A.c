#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 6840); // PRE: number of test cases must be in range [1, 6840]

    while (TC--) {
        int a, b, c, median;
        scanf("%d %d %d", &a, &b, &c);
        assert((1 <= a && a <= 20) && (1 <= b && b <= 20) && (1 <= c && c <= 20)); // PRE: each number must be in range [1, 20]
        
        if ((a > b && a < c) || (a < b && a > c)
            median = a;
        else if ((b > a && b < c) || (b < a && b > c)
            median = b;
        else
            median = c;

        printf("%d\n", median);
        assert((median > a && median < b) || (median < a && median > b) || // POST: median must be neither the minimum nor the maximum
               (median > b && median < c) || (median < b && median > c) ||
               (median > a && median < c) || (median < a && median > c));
    }
    return 0;
}