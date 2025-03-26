#include <stdio.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100); // PRE: 1 ≤ n ≤ 100

    double net = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        assert(x >= 0 && x <= 100); // PRE: 0 ≤ pi ≤ 100
        net += x;
    }
    double ans = net / n;
    printf("%.12f\n", ans);

    assert(ans >= 0 && ans <= 100); // POST: 0 ≤ ans ≤ 100
    return 0;
}