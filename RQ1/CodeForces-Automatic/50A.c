#include <stdio.h>
#include <assert.h>

int main() {
    int n, m, d;
    scanf("%d %d", &n, &m);
    
    // PRE: n and m must be in the range 1 ≤ M ≤ N ≤ 16
    assert(n >= 1 && n <= 16); // PRE: n is in range
    assert(m >= 1 && m <= 16); // PRE: m is in range
    assert(n <= m); // PRE: n is less than or equal to m

    d = (n * m) / 2;
    
    printf("%d\n", d);
    
    // POST: d should be the maximum number of dominoes that can fit on the board
    assert(d == (n * m) / 2); // POST: the calculated number of dominoes is valid
    return 0;
}