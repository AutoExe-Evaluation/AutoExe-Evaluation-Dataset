#include <stdio.h>
#include <assert.h>

int main()
{
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: 1 <= n <= 50
        int ct = 0;

        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            assert(x >= 1 && x <= 200); // PRE: 1 <= a_i <= 200
            assert(y >= 1 && y <= 200); // PRE: 1 <= b_i <= 200

            if (x > y) ct++;
        }
        printf("%d\n", ct);
        assert(ct >= 0); // POST: ct is valid
    }

    return 0;
}