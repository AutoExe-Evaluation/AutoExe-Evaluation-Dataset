#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 9261); // PRE: 1 <= t <= 9261
    while (TC--) 
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        assert(a >= 0 && a <= 20 && b >= 0 && b <= 20 && c >= 0 && c <= 20); // PRE: 0 <= a, b, c <= 20
        
        if (a == b + c || b == a + c || c == a + b)
        {
            printf("YES\n");
            assert(a == b + c || b == a + c || c == a + b); // POST: One number is the sum of the other two
        }
        else 
        {
            printf("NO\n");
        }
    }
    return 0;
}