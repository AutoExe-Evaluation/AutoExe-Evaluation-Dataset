#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: 1 ≤ TCS ≤ 100

    while (TCS--)
    {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 100); // PRE: 2 ≤ n ≤ 100
        
        int mx = 0, x = -1;
        for (int i = 2; i <= n; ++i)
        {
            int sum = 0;
            for (int j = 1; j * i <= n; ++j)
            {
                sum += j * i;
            }
            if (sum > mx)
            {
                mx = sum;
                x = i;
            }
        }
        assert(x >= 2 && x <= n); // POST: 2 ≤ x ≤ n
        printf("%d\n", x);
    }
    return 0;
}