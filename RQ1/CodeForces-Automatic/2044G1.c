#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 200000); // PRE: 2 ≤ n ≤ 2 * 10^5

        int* r = (int*)malloc((n + 1) * sizeof(int));
        int* deg = (int*)calloc(n + 1, sizeof(int));

        for (int i = 1; i <= n; ++i) {
            scanf("%d", &r[i]);
            assert(r[i] >= 1 && r[i] <= n && r[i] != i); // PRE: 1 ≤ r_i ≤ n, r_i ≠ i
            deg[r[i]]++;
        }

        int* q = (int*)malloc((n + 1) * sizeof(int));
        int front = 0, rear = 0;

        for (int i = 1; i <= n; ++i) {
            if (deg[i] == 0) {
                q[rear++] = i;
            }
        }

        int ct = 0;
        while (front < rear) {
            ct++;
            int size = rear - front;
            for (int i = 0; i < size; ++i) {
                int u = q[front++];
                int v = r[u];
                deg[v]--;
                if (deg[v] == 0) {
                    q[rear++] = v;
                }
            }
        }

        printf("%d\n", ct + 2);
        free(r);
        free(deg);
        free(q);
    }

    assert(TCS == 0); // POST: All test cases processed
    return 0;
}