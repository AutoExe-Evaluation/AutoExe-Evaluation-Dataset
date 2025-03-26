#include <stdio.h>
#include <assert.h>

int main()
{
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 10^5

    int ct1 = 0, ct2 = 0, ct3 = 0, ct4 = 0;
    for (int i = 0; i < n; ++i)
    {
        int x;
        scanf("%d", &x);
        assert(x >= 1 && x <= 4); // PRE: 1 ≤ si ≤ 4
        if (x == 1)
            ct1++;
        else if (x == 2)
            ct2++;
        else if (x == 3)
            ct3++;
        else
            ct4++;
    }
    
    int taxi = ct4;
    if (ct2 > 1)
    {
        taxi += ct2 / 2;
        ct2 = ct2 % 2;
    }
    while (ct3 > 0 && ct1 > 0)
    {
        taxi++;
        ct3--;
        ct1--;
    }
    if (ct3 > 0)
        taxi += ct3;
    if (ct1 > 0 && ct2 > 0)
    {
        taxi++;
        ct2--;
        ct1 -= 2;
    }
    while (ct2 > 0)
    {
        taxi++;
        ct2--;
    }
    while (ct1 > 0)
    {
        taxi++;
        ct1 -= 4;
    }
    
    printf("%d\n", taxi);
    assert(taxi >= (ct4 + (ct3 + 1) / 2 + (ct1 + 3) / 4 + (ct2 + 1) / 2)); // POST: minimum taxis calculated correctly
    return 0;
}