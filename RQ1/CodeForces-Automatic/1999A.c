#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS = 1;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 90); // PRE: Number of test cases should be in the range [1, 90].

    for (int TC = 1; TC <= TCS; ++TC)
    {
        int n;
        scanf("%d", &n);
        assert(n >= 10 && n <= 99); // PRE: Input number should be a two-digit positive integer.
        
        int sum = (n / 10) + (n % 10);
        printf("%d\n", sum);
        assert(sum >= 1 && sum <= 18); // POST: The sum of the digits will be in the range [1, 18].
    }
    
    return 0;
}