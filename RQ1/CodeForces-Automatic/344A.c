#include <stdio.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 100000

    char prev[3], curr[3];
    int ct = 1;

    scanf("%s", prev);
    for (int i = 1; i < n; i++) {
        scanf("%s", curr);
        if (curr[0] != prev[0]) ct++;
        prev[0] = curr[0]; // Update previous magnet
    }
    printf("%d\n", ct);
    assert(ct >= 1); // POST: ct ≥ 1, at least one group of magnets exists
    return 0;
}