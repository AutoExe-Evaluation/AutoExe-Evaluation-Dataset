#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 500); // PRE: Number of test cases is within limits

    for (int TC = 1; TC <= TCS; ++TC) {
        int n, odd = 0, even = 0;
        scanf("%d", &n);
        assert(n >= 1 && n <= 100); // PRE: Number of integers in a test case is within limits

        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: Each integer is within limits

            if (x & 1) odd++;
            else even++;
        }
        long long points;
        if (even) {
            points = odd + 1;
        } else {
            points = odd - 1;
        }
        assert(points >= -1); // POST: Maximum points is at least -1
        printf("%lld\n", points);
    }
    return 0;
}