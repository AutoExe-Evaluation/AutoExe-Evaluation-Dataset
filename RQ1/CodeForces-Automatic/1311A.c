#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases must be within valid range
    while (TC--) {
        int a, b;
        scanf("%d %d", &a, &b);
        assert(a >= 1 && a <= 1000000000); // PRE: a must be within valid range
        assert(b >= 1 && b <= 1000000000); // PRE: b must be within valid range

        int ct = 0;
        while (a != b) {
            if (a > b) {
                int d = a - b;
                if (d % 2 == 0) {
                    a = a - d;
                    ct++;
                } else {
                    a = a - d - 1;
                    ct++;
                }
            } else {
                int d = b - a;
                if (d % 2 != 0) {
                    a = a + d;
                    ct++;
                } else {
                    a = a + d - 1;
                    ct++;
                }
            }
        }
        printf("%d\n", ct);
        assert(ct >= 0); // POST: Count of moves must be non-negative
    }
    return 0;
}