#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main()
{
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10000
    while (TCS--) 
    {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        int* b = (int*)malloc(2 * n * sizeof(int));
        for(int i = 0; i < 2 * n; ++i) 
        {
            scanf("%lld", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: 1 <= b_i <= 10^9
        }

        // Sort array b
        for (int i = 0; i < 2 * n - 1; i++)
        {
            for (int j = i + 1; j < 2 * n; j++)
            {
                if (b[i] > b[j])
                {
                    int temp = b[i];
                    b[i] = b[j];
                    b[j] = temp;
                }
            }
        }

        int* a = (int*)malloc((2 * n + 1) * sizeof(int));
        int sum = 0;
        for(int i = 1; i < n; ++i)
        {
            a[2 * i - 2] = b[i];
            a[2 * i - 1] = b[n + i - 1];
            sum += b[n + i - 1] - b[i];
        }
        a[2 * n] = sum + b[2 * n - 1] + b[0];
        a[2 * n - 1] = b[0];

        printf("%lld", b[2 * n - 1]);
        for(int i = 0; i < 2 * n + 1; ++i)
            printf(" %lld", a[i]);
        printf("\n");

        free(b);
        free(a);
    }
    return 0;
    assert(0 < a[0] && a[0] <= 1000000000000000000); // POST: a[0] is a positive integer
}