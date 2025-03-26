#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int n, a, b, c;
    scanf("%d", &n);
    int v[3];
    for (int i = 0; i < 3; ++i)
    {
        scanf("%d", &v[i]);
    }

    // PRE: n > 0 and a, b, c > 0
    assert(n > 0 && a > 0 && b > 0 && c > 0);

    // Sorting v array using simple selection sort
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (v[i] > v[j])
            {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }

    int cts[100] = {0}; // Array to store possible cuts, limit of 100 for safety
    int temp, ct, tct;
    
    if (n % v[0] == 0)
    {
        cts[0] = n / v[0];
    }
    else
    {
        temp = n;
        ct = 0;
        while (temp > 0)
        {
            temp = temp - v[1];
            ct++;
            if (temp % v[0] == 0 && temp >= v[0])
            {
                ct = ct + temp / v[0];
                temp = temp % v[0];
                break;
            }
        }
        if (temp == 0)
            cts[0] = ct;

        temp = n;
        ct = 0;
        while (temp > 0)
        {
            temp = temp - v[2];
            ct++;
            if (temp % v[0] == 0 && temp >= v[0])
            {
                ct = ct + temp / v[0];
                temp = temp % v[0];
                break;
            }
        }
        if (temp == 0)
            cts[1] = ct;

        ct = 0;
        while (n > 0)
        {
            n = n - v[2];
            ct++;
            temp = n;
            tct = ct;
            while (temp > 0)
            {
                temp = temp - v[1];
                tct++;
                if (temp % v[0] == 0 && temp >= v[0])
                {
                    tct = tct + temp / v[0];
                    temp = temp % v[0];
                    break;
                }
            }
            if (temp == 0)
                cts[2] = tct;
        }
    }
    
    int ans = cts[0];
    for (int i = 1; i < 3; i++)
    {
        if (cts[i] > ans)
            ans = cts[i];
    }
    
    // POST: ans >= 0 and can be achieved by cutting the ribbon according to given lengths
    assert(ans >= 0);
    printf("%d\n", ans);
    return 0;
}