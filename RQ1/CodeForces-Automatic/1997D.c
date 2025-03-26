#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef long long ll;

ll dfs(int node, int *v, int **adj, int *size) {
    int mn = INT_MAX;
    for (int i = 0; i < size[node]; i++) {
        mn = (int)(mn < dfs(adj[node][i], v, adj, size) ? mn : dfs(adj[node][i], v, adj, size));
    }
    if (node == 0) return mn + v[0];
    if (mn == INT_MAX) return v[node];
    if (v[node] >= mn) return mn;
    return (mn + v[node]) / 2;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4
    for (int TC = 1; TC <= TCS; TC++) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 200000); // PRE: 2 <= n <= 2 * 10^5
        
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 0 && v[i] <= 1000000000); // PRE: 0 <= a_i <= 10^9
        }
        
        int **adj = (int **)malloc(n * sizeof(int *));
        int *size = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            adj[i] = (int *)malloc(n * sizeof(int));
            size[i] = 0;
        }
        
        for (int i = 1; i < n; i++) {
            int p;
            scanf("%d", &p);
            p--;
            assert(p >= 0 && p < n); // PRE: 1 <= p_i <= n
            adj[p][size[p]++] = i;
        }
        
        ll result = dfs(0, v, adj, size);
        printf("%lld\n", result);
        assert(result >= 0); // POST: The result must be non-negative
        
        free(v);
        for (int i = 0; i < n; i++) {
            free(adj[i]);
        }
        free(adj);
        free(size);
    }
    return 0;
}