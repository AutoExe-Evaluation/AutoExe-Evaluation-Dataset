#include <stdio.h>
#include <assert.h>

int main() {
    int i, n, t, count, ans;

    scanf("%d", &t);
    assert(t >= 1 && t <= 1000); // PRE: number of test cases is within bounds

    while (t--) {
        scanf("%d", &n);
        assert(n >= 1 && n <= 100); // PRE: array length is within bounds

        int a[100]; // since n is at most 100
        ans = 0;
        count = 0;

        for (i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            assert(a[i] == 0 || a[i] == 1); // PRE: array elements are binary

            if (a[i] == 0) {
                count++;
            } else {
                if (count > ans) {
                    ans = count;
                }
                count = 0;
            }
        }
        if (count > ans) {
            ans = count;
        }
        printf("%d\n", ans);
        assert(ans >= 0); // POST: longest blank space is non-negative
    }
    
    return 0;
}