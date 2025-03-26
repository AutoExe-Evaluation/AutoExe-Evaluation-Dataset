#include <stdio.h>
#include <assert.h>

int main()
{
    int n, h;
    scanf("%d %d", &n, &h);
    assert(n >= 1 && n <= 1000); // PRE: number of friends is within valid range
    assert(h >= 1 && h <= 1000); // PRE: height of fence is within valid range

    int w = 0;
    for (int i = 0; i < n; ++i)
    {
        int x;
        scanf("%d", &x);
        assert(x >= 1 && x <= 2 * h); // PRE: height of each friend is within valid range
        if (x > h) w += 2;
        else w++;
    }
    
    printf("%d\n", w);
    assert(w >= n && w <= 2 * n); // POST: minimum width is at least n and at most 2n
    return 0;
}