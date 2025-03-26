#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: number of test cases is within bounds

    while (TCS--) {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 3 && m < n && n <= 100); // PRE: n and m are within specified limits

        if (n % m == 0) {
            printf("YES\n");
            assert(m >= 3 && n > m); // POST: a convex polygon is possible
        } else {
            printf("NO\n");
            assert(!(m >= 3 && n > m)); // POST: a convex polygon is not possible
        }
    }

    return 0;
}