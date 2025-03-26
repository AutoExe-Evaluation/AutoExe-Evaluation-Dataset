#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: 1 ≤ t ≤ 500
    while (TC--) {
        int n;
        char s[101];
        scanf("%d%s", &n, s);
        assert(n >= 1 && n <= 100); // PRE: 1 ≤ n ≤ 100
        int mx = 0;
        
        for (int i = 0; i < n; i++) {
            int ct = 1;
            for (int j = i + 1; j < n; j++) {
                if (s[j] == s[i])
                    ct++;
                else {
                    if (ct > mx)
                        mx = ct;
                    ct = 1;
                    break;
                }
            }
            if (ct > mx)
                mx = ct;
        }
        
        int greater_mx = mx;
        mx = 0;
        
        for (int i = 0; i < n; i++) {
            int ct = 1;
            for (int j = i + 1; j < n; j++) {
                if (s[j] == s[i])
                    ct++;
                else {
                    if (ct > mx)
                        mx = ct;
                    ct = 1;
                    break;
                }
            }
            if (ct > mx)
                mx = ct;
        }
        
        int smaller_mx = mx;
        int result = greater_mx > smaller_mx ? greater_mx + 1 : smaller_mx + 1;
        printf("%d\n", result);
        assert(result > 0); // POST: The minimum cost is always greater than 0
    }
    return 0;
}