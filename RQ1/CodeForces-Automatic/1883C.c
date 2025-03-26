#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ll long long

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10000

    while (TCS--)
    {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(n >= 2 && n <= 100000); // PRE: 2 ≤ n ≤ 100000
        assert(k >= 2 && k <= 5); // PRE: 2 ≤ k ≤ 5
        int *mp = (int *)calloc(k, sizeof(int));
        int ct = 0;

        for (int i = 0; i < n; ++i)
        {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= 10); // PRE: 1 ≤ a_i ≤ 10
            if (x % 2 == 0) ct++;
            mp[x % k]++;
        }

        if (mp[0])
        {
            printf("0\n");
            free(mp);
            continue;
        }

        int ans = k - (mp[k - 1] ? (k - 1) : 0);
        ct = ct < 2 ? 2 - ct : 0;
        if (k % 4 == 0)
            ans = ct < ans ? ct : ans;

        printf("%d\n", ans);
        assert(ans >= 0); // POST: Minimum operations needed should be non-negative

        free(mp);
    }
    return 0;
}