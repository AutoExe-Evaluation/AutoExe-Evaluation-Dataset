#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases is between 1 and 100.
    
    while (TC--) 
    {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 100); // PRE: Size of the desired permutation is between 1 and 100.

        if(n == 1) 
        {
            printf("1\n");
            assert(n == 1); // POST: For n=1, output is 1.
        } 
        else if(n % 2 != 0) 
        {
            printf("-1\n");
            assert(n % 2 != 0); // POST: For odd n, output is -1.
        } 
        else 
        {
            for(int i = 1; i <= n; i += 2)
            {
                printf("%d %d ", i + 1, i);
            }
            printf("\n");
            assert(n % 2 == 0); // POST: For even n, output is a valid permutation.
        }
    }
    return 0;
}