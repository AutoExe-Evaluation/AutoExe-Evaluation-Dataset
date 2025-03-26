#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is within bounds
    while (TC--) 
    {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 100000); // PRE: Size of array is within bounds
        int a[n];
        for(int i=0; i<n; i++)
        {
            scanf("%d", &a[i]);
            assert(a[i] == 0 || a[i] == 1); // PRE: Array elements are either 0 or 1
        }
        int ct = 0;
        for(int i=0, j=n-1; i<j; i++, j--)
        {
            if(a[i] == 1 && a[j] == 0) ct++;
            else if(a[i] == 1 && a[j] == 1) i--;
            else if(a[i] == 0 && a[j] == 0) j++;
        }
        printf("%d\n", ct);
        assert(ct >= 0); // POST: Number of operations is non-negative
    }
    return 0;
}