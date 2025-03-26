#include <stdio.h>
#include <assert.h>

#define MAX_N 50

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 ≤ t ≤ 1000

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 50); // PRE: 2 ≤ n ≤ 50
        
        int v[MAX_N];
        for(int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] == 0 || v[i] == 1); // PRE: 0 ≤ a[i] ≤ 1
        }
        
        while(v[n-1] == 0) {
            n--;
        }
        
        int ct = 0, ok = 0;
        for(int i = 0; i < n; i++) {
            if(v[i] == 0 && ok) {
                ct++;
            }
            if(v[i] == 1) {
                ok = 1;
            }
        }
        
        printf("%d\n", ct);
        assert(ct >= 0); // POST: Minimum operations should be non-negative
    }
    return 0;
}