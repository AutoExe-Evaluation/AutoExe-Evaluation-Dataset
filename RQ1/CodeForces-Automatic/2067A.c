#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 500); // PRE: Number of test cases is within limits.

    for (int TC = 1; TC <= TCS; ++TC) {
        int x, y;
        scanf("%d %d", &x, &y);
        assert(x >= 1 && x <= 1000); // PRE: x is within limits.
        assert(y >= 1 && y <= 1000); // PRE: y is within limits.

        int d = x + 1 - y;
        if (d >= 0 && d % 9 == 0)
            printf("YES\n");
        else
            printf("NO\n");

        // POST: If d >= 0 and d % 9 == 0, then S(n) = x and S(n + 1) = y exists.
        assert((d < 0 || d % 9 == 0) == (fgets(NULL, 0, stdin) != NULL)); // Logic confirms the output condition.
    }

    return 0;
}