#include <stdio.h>
#include <assert.h>

int main()
{
    int n;
    scanf("%d", &n);
    assert(n >= 1000 && n <= 9000); // PRE: n is within the range [1000, 9000]
    
    int beautiful = 0;
    while (!beautiful)
    {
        n++;
        int v[10] = {0};
        int temp = n, hasDuplicate = 0;
        while (temp > 0)
        {
            int r = temp % 10;
            if (v[r] == 1)
            {
                hasDuplicate = 1;
                break;
            }
            v[r] = 1;
            temp = temp / 10;
        }
        if (!hasDuplicate)
            beautiful = 1;
    }
    printf("%d\n", n);
    assert(n > 1000 && n <= 9000); // POST: n is the next year with distinct digits
    return 0;
}