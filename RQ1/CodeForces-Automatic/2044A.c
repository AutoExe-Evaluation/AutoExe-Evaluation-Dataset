#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS = 1;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 99); // PRE: 1 <= TCS <= 99

    for (int TC = 1; TC <= TCS; ++TC)
    {
        int n;
        scanf("%d", &n);
        
        assert(n >= 2 && n <= 100); // PRE: 2 <= n <= 100
        
        int result = n - 1;
        printf("%d\n", result);
        
        assert(result == n - 1); // POST: result equals n - 1
    }
    
    return 0;
}