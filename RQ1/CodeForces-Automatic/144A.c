#include <stdio.h>
#include <limits.h>
#include <assert.h>

int main()
{
    int n;
    scanf("%d", &n);
    assert(n >= 2 && n <= 100); // PRE: n is between 2 and 100 inclusive
    int line[100];
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &line[i]);
        assert(line[i] >= 1 && line[i] <= 100); // PRE: Each height ai is between 1 and 100 inclusive
    }
    
    int min, min_pos, max, max_pos;
    min = max_pos = INT_MAX;
    max = min_pos = INT_MIN;
    
    for(int i = 0; i < n; ++i)
    {
        if(line[i] > max)
        {
            max = line[i];
            max_pos = i;
        }
    }
    
    for(int i = n - 1; i >= 0; --i)
    {
        if(line[i] < min)
        {
            min = line[i];
            min_pos = i;
        }
    }
    
    int ans;
    if(max_pos < min_pos)
    {
        ans = max_pos + (n - 1 - min_pos);
    }
    else 
    {
        ans = max_pos + (n - 1 - min_pos) - 1;
    }
    
    printf("%d\n", ans);
    assert(ans >= 0); // POST: The result is non-negative, as the number of swaps cannot be negative
    return 0;
}