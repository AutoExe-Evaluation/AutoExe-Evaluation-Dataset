#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 ≤ t ≤ 1000

    while (TC--) {
        int x, k;
        scanf("%d %d", &x, &k);
        assert(x >= 1 && x <= 100); // PRE: 1 ≤ x ≤ 100
        assert(k >= 2 && k <= 100); // PRE: 2 ≤ k ≤ 100

        if (x % k != 0) {
            printf("1\n%d\n", x);
            assert(x % k != 0); // POST: Reachable in 1 move when x % k != 0
        } else {
            printf("2\n%d %d\n", k + 1, x - k - 1);
            assert((k + 1 + (x - k - 1)) == x); // POST: Reachable in 2 moves summing to x
            assert((k + 1) % k != 0 && (x - k - 1) % k != 0); // POST: Moves are not divisible by k
        }
    }
    return 0;
}