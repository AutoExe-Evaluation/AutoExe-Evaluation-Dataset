#include <stdio.h>
#include <limits.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= t <= 1000

    while (TC--) {
        int n, t1, t2, t;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        t = t1 = t2 = INT_MAX;

        for(int i = 0; i < n; ++i) {
            int x;
            char s[3];
            scanf("%d %s", &x, s);
            assert(x >= 1 && x <= 200000); // PRE: 1 <= m_i <= 2 * 10^5
            if(s[0] == '1') t1 = x < t1 ? x : t1;
            if(s[1] == '1') t2 = x < t2 ? x : t2;
            if(s[0] == '1' && s[1] == '1') t = x < t ? x : t;
        }
        
        // POST: The minimum time required to gain both skills is accurately calculated
        if(t1 == INT_MAX || t2 == INT_MAX) {
            printf("-1\n");
            assert(t1 != INT_MAX && t2 != INT_MAX); // POST: t1 and t2 must not be INT_MAX for skills to be obtained
        }
        else {
            int result = t < t1 + t2 ? t : t1 + t2;
            printf("%d\n", result);
            assert(result >= 0); // POST: The output must be a non-negative integer
        }
    }
    return 0;
}