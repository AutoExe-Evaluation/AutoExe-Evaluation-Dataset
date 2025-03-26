#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long int ll;

typedef struct {
    ll first;
    int second;
} Pair;

int compare(const void *a, const void *b) {
    return ((Pair *)b)->first - ((Pair *)a)->first;
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is within bounds

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 200000); // PRE: Number of colors is within bounds

        ll *a = (ll *)malloc(n * sizeof(ll));
        ll *b = (ll *)malloc(n * sizeof(ll));
        Pair *s = (Pair *)malloc(n * sizeof(Pair));

        for(int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: Alice's marbles are within bounds
        }
        for(int i = 0; i < n; i++) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: Bob's marbles are within bounds
        }

        for(int i = 0; i < n; i++) {
            s[i].first = a[i] + b[i];
            s[i].second = i;
        }

        qsort(s, n, sizeof(Pair), compare);

        int t = 1;
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            int idx = s[i].second;
            if(t) {
                ans += a[idx] - 1;
            } else {
                ans -= b[idx] - 1;
            }
            t ^= 1;
        }

        printf("%lld\n", ans);
        // POST: The score is correctly calculated based on optimal play
        assert(ans >= -1000000000 && ans <= 1000000000); // POST: Score is within reasonable bounds

        free(a);
        free(b);
        free(s);
    }
    return 0;
}