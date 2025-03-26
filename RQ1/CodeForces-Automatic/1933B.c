#include <stdio.h>

#define FAST_IO (setbuf(stdout, NULL))

int main() {
    FAST_IO;
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 104); // PRE: 1 ≤ t ≤ 10^4

    while (TC--) {
        int n, sum = 0, flag = 0;
        scanf("%d", &n);
        assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 10^5

        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= 10000); // PRE: 1 ≤ ai ≤ 10^4
            if (x % 3 == 1)
                flag = 1;
            sum += x;
        }

        int moves;
        if (sum % 3 == 0)
            moves = 0;
        else if (flag)
            moves = 1;
        else
            moves = 3 - sum % 3;

        printf("%d\n", moves);
        assert(moves >= 0); // POST: moves should be non-negative
    }
    return 0;
}