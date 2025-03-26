#include <stdio.h>
#include <assert.h>

int main() {
    int t;
    scanf("%d", &t);
    assert(t >= 1 && t <= 10000); // PRE: 1 ≤ t ≤ 10^4
    while (t--) {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 1000000000 && m >= 1 && m <= 1000000000); // PRE: 1 ≤ n, m ≤ 10^9

        if ((n + m) % 2 == 0) {
            printf("Tonya\n");
        } else {
            printf("Burenka\n");
        }
    }
    return 0;
}

// POST: The output is correctly determined based on the inputs, and the winner is always printed based on optimal moves.