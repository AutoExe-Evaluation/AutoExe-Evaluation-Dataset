#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= TCS <= 1000

    while (TCS--)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        
        assert(a >= 1 && a <= 10); // PRE: 1 <= a <= 10
        assert(b >= 1 && b <= 10); // PRE: 1 <= b <= 10
        assert(c >= 1 && c <= 10); // PRE: 1 <= c <= 10
        
        int mn = INT_MAX;

        for (int i = 1; i <= 10; ++i)
        {
            int diff = abs(a - i) + abs(b - i) + abs(c - i);
            if (diff < mn)
                mn = diff;
        }
        
        printf("%d\n", mn);
        
        assert(mn >= 0); // POST: The minimum distance cannot be negative
    }
    
    return 0;
}