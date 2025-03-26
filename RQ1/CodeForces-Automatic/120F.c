#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define M 110

int g[M][M], depth[M];

void dfs(int vertex, int parent) {
    for (int child = 1; child < M; child++) {
        if (g[vertex][child]) {
            if (child == parent) continue;
            depth[child] = depth[vertex] + 1;
            dfs(child, vertex);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100); // PRE: number of spiders should be within range
    
    long long ans = 0;
    while (n--) {
        int m;
        scanf("%d", &m);
        assert(m >= 2 && m <= 100); // PRE: number of beads in a spider should be within range
        memset(g, 0, sizeof(g));
        for (int i = 0; i < m - 1; ++i) {
            int v, u;
            scanf("%d %d", &v, &u);
            g[v][u] = 1;
            g[u][v] = 1;
        }
        int mx = 0;
        for (int i = 1; i <= m; ++i) {
            memset(depth, 0, sizeof(depth));
            dfs(i, 0);
            for (int j = 1; j < M; j++) {
                if (depth[j] > mx) {
                    mx = depth[j];
                }
            }
        }
        ans += mx;
    }
    printf("%lld\n", ans);
    assert(ans >= 0); // POST: final length must be non-negative
    return 0;
}