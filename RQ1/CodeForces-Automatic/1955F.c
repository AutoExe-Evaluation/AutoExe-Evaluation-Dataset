#include <stdio.h>

#define FAST_IO (setbuf(stdout, NULL))

int main()
{
    FAST_IO;
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases should be within the defined limits.

    while (TC--) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        assert(a >= 0 && a <= 200); // PRE: Number of ones should be within the defined limits.
        assert(b >= 0 && b <= 200); // PRE: Number of twos should be within the defined limits.
        assert(c >= 0 && c <= 200); // PRE: Number of threes should be within the defined limits.
        assert(d >= 0 && d <= 200); // PRE: Number of fours should be within the defined limits.

        int ans = a / 2 + b / 2 + c / 2 + d / 2;
        if (a % 2 && b % 2 && c % 2)
            ans++;
        
        printf("%d\n", ans);
        assert(ans >= 0); // POST: The number of wins for Bob should be non-negative.
    }
    
    return 0;
}