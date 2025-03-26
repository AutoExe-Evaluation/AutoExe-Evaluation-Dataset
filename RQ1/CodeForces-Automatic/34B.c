#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    
    assert(n >= 1 && m >= 1 && m <= n && n <= 100); // PRE: 1 ≤ m ≤ n ≤ 100
    
    int *v = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &v[i]);
        assert(v[i] >= -1000 && v[i] <= 1000); // PRE: -1000 ≤ ai ≤ 1000
    }

    // Sort the array
    for(int i = 0; i < n - 1; ++i)
    {
        for(int j = i + 1; j < n; ++j)
        {
            if(v[i] > v[j])
            {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }

    int sum = 0;
    for(int i = 0; i < m; ++i)
    {
        if(v[i] >= 0)
            break;
        else
            sum += abs(v[i]);
    }
    
    printf("%d\n", sum);
    
    assert(sum >= 0); // POST: sum should be non-negative
    free(v);
    
    return 0;
}