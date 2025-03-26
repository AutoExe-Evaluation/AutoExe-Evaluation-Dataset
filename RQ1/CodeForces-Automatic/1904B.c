#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

typedef struct {
    int first;
    int second;
} Pair;

int main() {
    int t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 5000); // PRE: 1 ≤ t ≤ 5000
    while (t--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 10^5
        Pair *v = (Pair *)malloc(n * sizeof(Pair));
        int *pre = (int *)malloc(n * sizeof(int));
        int *ans = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; ++i) {
            scanf("%lld", &v[i].first);
            assert(v[i].first >= 1 && v[i].first <= 1000000000); // PRE: 1 ≤ a_i ≤ 10^9
            v[i].second = i;
        }

        // Sort pairs based on the first element
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (v[j].first > v[j + 1].first) {
                    Pair temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }

        pre[0] = v[0].first;
        for (int i = 1; i < n; ++i) {
            pre[i] = pre[i - 1] + v[i].first;
        }

        ans[v[n - 1].second] = n - 1;
        int last = n - 1;

        for (int i = n - 2; i >= 0; --i) {
            if (pre[i] < v[i + 1].first) {
                last = i;
            }
            ans[v[i].second] = last;
        }

        for (int i = 0; i < n; ++i) {
            printf("%lld ", ans[i]);
        }
        printf("\n");

        free(v);
        free(pre);
        free(ans);
    }
    // POST: The output reflects the maximum number of array elements that can be removed, corresponding to the conditions of each test case.
    return 0;
}