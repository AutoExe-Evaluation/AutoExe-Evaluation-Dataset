#include <stdio.h>
#include <assert.h>

int main() {
    int n, d;
    scanf("%d %d", &n, &d);
    assert(n >= 2 && n <= 2000); // PRE: n is in the range [2, 2000]
    assert(d >= 1 && d <= 106); // PRE: d is in the range [1, 106]
    
    int v[2000];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
        assert(v[i] >= 1 && v[i] <= 106); // PRE: bi is in the range [1, 106]
    }

    int ct = 0;
    for (int i = 1; i < n; ++i) {
        if (v[i] <= v[i - 1]) {
            int x = v[i - 1] - v[i];
            if (x == 0) {
                v[i] += d;
                ct++;
            } else if (x % d == 0) {
                int y = x / d;
                ct += y;
                v[i] += y * d;
            } else {
                int y = (x / d) + 1;
                ct += y;
                v[i] += y * d;
            }
        }
        if (v[i] == v[i - 1]) {
            v[i] += d;
            ct++;
        }
    }
    
    assert(ct >= 0); // POST: ct is non-negative
    printf("%d\n", ct);
    return 0;
}