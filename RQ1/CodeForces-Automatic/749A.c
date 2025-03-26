#include <stdio.h>
#include <assert.h>

int main()
{
    long long n;
    scanf("%lld", &n);
    assert(n >= 2 && n <= 100000); // PRE: n is within the bounds [2, 100000]
    
    printf("%lld\n", n / 2);
    while (n > 3)
    {
        printf("2 ");
        n -= 2;
    }
    printf("%lld\n", n);
    
    // POST: The sum of printed numbers is equal to the input n
    assert(n % 2 == 0 || n == 3); // The output should be valid since n is either even (for 2s) or 3 at the end
    return 0;
}