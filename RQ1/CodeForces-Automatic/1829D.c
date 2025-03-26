#include <stdio.h>
#include <assert.h>

int check(int n, int m) {
    assert(n > 0 && m > 0); // PRE: n and m must be positive integers
    if (n == m) return 1;
    else if (n % 3 != 0 || n < m) return 0;
    else return check(n / 3, m) || check(2 * n / 3, m);
}

int main() {
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= TC <= 1000
    while (TC--) {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 10000000 && m >= 1 && m <= 10000000); // PRE: 1 <= n, m <= 10^7
        int p = check(n, m);
        assert(p == 0 || p == 1); // POST: p should be either 0 or 1
        if (p) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}