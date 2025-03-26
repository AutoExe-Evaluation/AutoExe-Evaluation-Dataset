#include <stdio.h>
#include <assert.h>

#define int long long

void solve()
{
    int n;
    scanf("%lld", &n);
    assert(n >= 2 && n <= 1000); // PRE: n is within the range [2, 1000]
    
    int v[1000];
    int ct = 0;
    for(int i = 0; i < n; ++i)
    {
        scanf("%lld", &v[i]);
        assert(v[i] == 1 || v[i] == 2); // PRE: each element of v is either 1 or 2
        if(v[i] == 2)
            ct++;
    }

    if(ct == 0)
    {
        printf("1\n");
        assert(1 >= 1 && 1 <= n - 1); // POST: k (1) satisfies k's condition
    }
    else if(ct % 2)
    {
        printf("-1\n");
        assert(-1 == -1); // POST: no valid k exists
    }
    else
    {
        ct /= 2;
        int x = 0;
        for(int i = 0; i < n; ++i)
        {
            if(v[i] == 2)
                x++;
            if(x == ct)
            {
                printf("%lld\n", i + 1);
                assert(i + 1 >= 1 && i + 1 <= n - 1); // POST: k satisfies k's condition
                return;
            }
        }
    }
}

int main()
{
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: TC is within the range [1, 100]
    while (TC--) 
        solve();
}