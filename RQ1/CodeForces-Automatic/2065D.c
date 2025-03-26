#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

typedef struct {
    int sum;
    int index;
} Pair;

int compare(const void *a, const void *b) {
    return ((Pair*)b)->sum - ((Pair*)a)->sum;
}

// PRE: n, m > 0 and total elements for all test cases do not exceed 2 * 10^5
// POST: output the maximum score obtainable from the concatenated arrays
int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS > 0); // PRE: at least one test case

    while (TCS--) {
        int n, m;
        scanf("%lld %lld", &n, &m);
        assert(n > 0 && m > 0); // PRE: number of arrays and length of each array are positive

        int **mp = malloc(n * sizeof(int*));
        int *sums = malloc(n * sizeof(int));
        Pair *w = malloc(n * sizeof(Pair));

        for (int i = 0; i < n; i++) {
            mp[i] = malloc(m * sizeof(int));
            sums[i] = 0;
            for (int j = 0; j < m; j++) {
                scanf("%lld", &mp[i][j]);
                sums[i] += mp[i][j];
            }
            w[i].sum = sums[i];
            w[i].index = i;
        }
        qsort(w, n, sizeof(Pair), compare);

        int *v = malloc(n * m * sizeof(int));
        int index = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[index++] = mp[w[i].index][j];
            }
        }

        int *ans = malloc((n * m + 1) * sizeof(int));
        for (int i = 1; i <= n * m; i++) {
            ans[i] = v[i - 1] + ans[i - 1];
        }

        int sum = 0;
        for (int i = 0; i <= n * m; i++) {
            sum += ans[i];
        }

        printf("%lld\n", sum); // POST: the output is the maximum score

        free(sums);
        free(v);
        free(ans);
        for (int i = 0; i < n; i++) {
            free(mp[i]);
        }
        free(mp);
        free(w);
    }
    return 0;
}