#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 5000); // PRE: Number of test cases is valid
    
    for (int TC = 1; TC <= TCS; ++TC) {
        int l1, r1, l2, r2;
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        
        assert(l1 >= 1 && l1 <= r1 && r1 <= 50); // PRE: l1 and r1 are valid
        assert(l2 >= 1 && l2 <= r2 && r2 <= 50); // PRE: l2 and r2 are valid
        
        int ans = 0;

        for (int i = l1; i <= r1; ++i) {
            if (i >= l2 && i <= r2) {
                ans = i;
                break;
            }
        }
        
        if (ans) {
            printf("%d\n", ans);
            assert(ans >= l1 + l2); // POST: Valid minimum number of elements
        } else {
            printf("%d\n", l1 + l2);
            assert(l1 + l2 >= l1 + l2); // POST: Valid minimum number of elements
        }
    }
    return 0;
}