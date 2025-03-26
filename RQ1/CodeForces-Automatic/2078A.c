#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 500); // PRE: 1 <= TCS <= 500

    while (TCS--) 
    {
        int n, x;
        scanf("%d %d", &n, &x);
        assert(n >= 1 && n <= 100); // PRE: 1 <= n <= 100
        assert(x >= 1 && x <= 100); // PRE: 1 <= x <= 100
        
        int v[100];
        int sum = 0;

        for (int i = 0; i < n; i++) 
        {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 100); // PRE: 1 <= a_i <= 100
            sum += v[i];
        }

        if (sum % n == 0 && sum / n == x) 
        {
            printf("YES\n");
            assert(sum / n == x); // POST: average equals x
        } 
        else 
        {
            printf("NO\n");
            assert(sum % n != 0 || sum / n != x); // POST: average does not equal x
        }
    }
    return 0;
}