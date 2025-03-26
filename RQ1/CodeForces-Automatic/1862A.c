#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: 1 <= t <= 100
    
    while (TC--) {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 20 && m >= 1 && m <= 20); // PRE: 1 <= n, m <= 20
        
        char carpet[20][21]; // 20 rows, 21 columns for null terminator
        for (int i = 0; i < n; i++) {
            scanf("%s", carpet[i]);
        }
        
        char s[] = "vika";
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (carpet[j][i] == s[cnt]) {
                    cnt++;
                    break;
                }
            }
        }
        
        // POST: if cnt == 4, then "vika" was found; else, it wasn't
        if (cnt == 4) {
            printf("YES\n");
            assert(cnt == 4); // POST: vika is present
        } else {
            printf("NO\n");
            assert(cnt < 4); // POST: vika is not present
        }
    }
    
    return 0;
}