#include <stdio.h>
#include <assert.h>

int main()
{
    int t;
    scanf("%d", &t);
    assert(t >= 1 && t <= 10000); // PRE: 1 ≤ t ≤ 10^4
    while (t--)
    {
        int n, i, min_even = 0, min_odd = 0, odd_count = 0, even_count = 0;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 ≤ n ≤ 2 * 10^5
        int a[n];
        for (i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: 1 ≤ a_i ≤ 10^9
            if (a[i] % 2 != 0)
            {
                odd_count++;
                if (odd_count == n)
                    break;
                if (min_odd == 0 || min_odd > a[i])
                {
                    min_odd = a[i];
                }
            }
            else
            {
                even_count++;
                if (even_count == n)
                    break;
                if (min_even == 0 || min_even > a[i])
                {
                    min_even = a[i];
                }
            }
        }
        assert(odd_count + even_count == n); // POST: all elements processed
        if (odd_count == n || even_count == n || min_even > min_odd)
            printf("Yes\n");
        else
            printf("No\n");
    }
}