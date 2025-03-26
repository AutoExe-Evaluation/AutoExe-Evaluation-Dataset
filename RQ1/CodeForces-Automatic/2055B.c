#include <stdio.h>
#include <assert.h>

#define int long long

int main() 
{
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is valid

    while (TCS--) 
    {
        int n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 200000); // PRE: Number of materials is valid
        int a[n + 1], b[n + 1], pre[n + 2] = {0};

        for (int i = 1; i <= n; ++i) 
        {
            scanf("%lld", &a[i]);
            assert(a[i] >= 0 && a[i] <= 1000000000); // PRE: Amount of material is valid
        }

        for (int i = 1; i <= n; ++i) 
        {
            scanf("%lld", &b[i]);
            assert(b[i] >= 0 && b[i] <= 1000000000); // PRE: Required amount of material is valid
            if (b[i] > a[i]) 
            {
                int need = b[i] - a[i];
                pre[1] -= need;
                pre[i] += 2 * need;
                pre[i + 1] -= 2 * need; 
                pre[n + 1] += need;      
            }
        }

        for (int i = 1; i <= n; ++i) 
        {
            pre[i] += pre[i - 1];
        }

        for (int i = 1; i <= n; ++i) 
        {
            assert(a[i] + pre[i] >= 0); // POST: Non-negative resources after operation
            if (a[i] + pre[i] < b[i]) 
            {
                printf("NO\n");
                break;
            }
            if (i == n) 
            {
                printf("YES\n");
            }
        }
    }
    return 0;
}