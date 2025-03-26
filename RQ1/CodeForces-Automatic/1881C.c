#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXN 1000

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases must be in range [1, 100].

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n % 2 == 0 && n >= 2 && n <= 1000); // PRE: n must be even and in range [2, 1000].
        
        char s[MAXN][MAXN];
        for (int i = 0; i < n; i++)
            scanf("%s", s[i]);

        char v[4];
        int ans = 0;

        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n / 2; j++) {
                int k = 0;
                v[k++] = s[i][j];
                v[k++] = s[j][n-i-1];
                v[k++] = s[n-j-1][i];
                v[k++] = s[n-i-1][n-j-1];

                // Sort the array
                for (int a = 0; a < 4; a++) {
                    for (int b = a + 1; b < 4; b++) {
                        if (v[a] > v[b]) {
                            char temp = v[a];
                            v[a] = v[b];
                            v[b] = temp;
                        }
                    }
                }

                for (int a = 0; a < 4; a++)
                    ans += v[3] - v[a];
            }
        }
        printf("%d\n", ans);
        assert(ans >= 0); // POST: The answer must be non-negative, as it represents the number of operations.
    }
    return 0;
}