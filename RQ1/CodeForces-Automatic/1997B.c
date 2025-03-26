#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_N 200000

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4
    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        char v[2][MAX_N + 1];
        for (int i = 0; i < 2; i++) {
            scanf("%s", v[i]);
            assert(strlen(v[i]) == n); // Check string length
        }
        
        int ans = 0;
        
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                int ct = 0;
                if (j + 1 < n && v[i][j + 1] == '.') ct++;
                if (j - 1 >= 0 && v[i][j - 1] == '.') ct++;
                if (ct < 2) continue;

                if (i == 0) {   
                    if (v[i + 1][j] == '.' && v[i + 1][j - 1] == 'x' && v[i + 1][j + 1] == 'x') ans++;
                } else {
                    if (v[i - 1][j] == '.' && v[i - 1][j - 1] == 'x' && v[i - 1][j + 1] == 'x') ans++;
                }
            }
        }
        
        printf("%d\n", ans);
        assert(ans >= 0); // POST: ans should be non-negative
    }
    return 0;
}