#include <stdio.h>
#include <assert.h> 

int main() {
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is within limits

    while (TC--) {
        int l, r;
        scanf("%d %d", &l, &r);
        assert(l >= 1 && l < r && r <= 1000000000); // PRE: l and r are within limits
        
        if (2 * l > r) {
            printf("-1 -1\n");
            assert(-1 == -1 && -1 == -1); // POST: Output indicates impossibility
        } else {
            printf("%d %d\n", l, 2 * l);
            assert(l <= 2 * l && 2 * l <= r); // POST: x = l, y = 2 * l satisfy conditions
        }
    }

    return 0;
}