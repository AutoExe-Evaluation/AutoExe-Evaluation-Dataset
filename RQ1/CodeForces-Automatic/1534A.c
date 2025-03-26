#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAXN 50

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: 1 <= TCS <= 100
    while (TCS--) {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 50 && m >= 1 && m <= 50); // PRE: 1 <= n, m <= 50
        char v1[MAXN][MAXN], v2[MAXN][MAXN];
        bool f1 = true, f2 = true;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j) % 2) {
                    v1[i][j] = 'R';
                    v2[i][j] = 'W';
                } else {
                    v1[i][j] = 'W';
                    v2[i][j] = 'R';
                }
                char c;
                scanf(" %c", &c);
                assert(c == 'R' || c == 'W' || c == '.'); // PRE: c is one of 'R', 'W', or '.'
                if (c != '.') {
                    if (c != v1[i][j]) f1 = false;
                    if (c != v2[i][j]) f2 = false;
                }
            }
        }

        if (f1 || f2) {
            printf("YES\n");
            if (f1) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        printf("%c", v1[i][j]);
                    }
                    printf("\n");
                }
            } else {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        printf("%c", v2[i][j]);
                    }
                    printf("\n");
                }
            }
        } else {
            printf("NO\n");
        }
        // POST: The grid is colored such that no two adjacent cells have the same color if possible.
        assert(f1 || f2); // POST: Either configuration must be valid.
    }
    return 0;
}