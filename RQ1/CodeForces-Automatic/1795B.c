#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXN 51

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= t <= 1000

    while (TC--) {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(n >= 1 && n <= 50); // PRE: 1 <= n <= 50
        assert(k >= 1 && k <= 50); // PRE: 1 <= k <= 50

        int v[MAXN] = {0};
        while (n--) {
            int l, r;
            scanf("%d %d", &l, &r);
            assert(l >= 1 && r >= l && r <= 50); // PRE: 1 <= l_i <= r_i <= 50
            if (l == r && k == l)
                v[k]++;
            else if (l <= k && r >= k) {
                for (int i = l; i <= r; ++i)
                    v[i]++;
            }
        }
        int max_count = 0, index = -1;
        for (int i = 0; i < MAXN; i++) {
            if (v[i] > max_count) {
                max_count = v[i];
                index = i;
            }
        }
        max_count = 0;
        for (int i = 0; i < MAXN; i++) {
            if (v[i] == v[index])
                max_count++;
        }
        
        // POST: After processing, check if point k can be ideal
        if (index == k && max_count == 1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}