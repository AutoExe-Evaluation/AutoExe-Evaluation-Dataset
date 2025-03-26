#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int t;
    scanf("%d", &t);
    assert(t >= 1 && t <= 10000); // PRE: Number of test cases must be within the range

    while (t--) {
        int n, m;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: Size of array must be within the range

        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: Elements of array a must be within the range
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: Elements of array b must be within the range
        }
        scanf("%d", &m);
        assert(m >= 1 && m <= 200000); // PRE: Number of modification operations must be within the range

        int *d = (int *)malloc(m * sizeof(int));
        int *mp = (int *)calloc(1000000001, sizeof(int));
        for (int i = 0; i < m; i++) {
            scanf("%d", &d[i]);
            assert(d[i] >= 1 && d[i] <= 1000000000); // PRE: Elements of array d must be within the range
            mp[d[i]]++;
        }

        int f = 1;
        for (int i = 0; i < n; i++) {
            if (a[i] == b[i]) continue;
            if (mp[b[i]]) {
                mp[b[i]]--;
            } else {
                f = 0;
                break;
            }
        }
        
        if (f && !mp[d[m - 1]]) f = 0;
        printf(f ? "YES\n" : "NO\n");

        free(a);
        free(b);
        free(d);
        free(mp);
    }

    assert(1); // POST: The program will produce valid outputs for given inputs within preconditions
    return 0;
}