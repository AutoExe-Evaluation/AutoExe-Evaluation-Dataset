#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10^4

    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= n); // PRE: 1 <= a_i <= n
        }

        int *m = (int *)calloc(n + 2, sizeof(int));
        m[v[0]]++;

        for (int i = 1; i < n; ++i) {
            if (m[v[i] - 1] == 0 && m[v[i] + 1] == 0) {
                printf("NO\n");
                free(v);
                free(m);
                return 0;
            }
            m[v[i]]++;
        }

        printf("YES\n");
        free(v);
        free(m);
    }

    return 0;
} // POST: All passengers' seats followed the recommendations if the program outputs "YES" for valid inputs