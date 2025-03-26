#include <stdio.h>
#include <assert.h>

#define MAX_N 100

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 500); // PRE: 1 ≤ TCS ≤ 500

    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 100); // PRE: 2 ≤ n ≤ 100
        
        int v[MAX_N];
        for(int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: 1 ≤ a_i ≤ 10^9
        }
        
        int ans = 0;
        for(int i = 0; i < n - 1; ++i) {
            int p = v[i] + v[n - 1];
            if(p > ans) 
                ans = p;
        }
        printf("%d\n", ans);
        assert(ans >= 2 && ans <= 2000000000); // POST: Maximum pages read is valid
    }
    return 0;
}