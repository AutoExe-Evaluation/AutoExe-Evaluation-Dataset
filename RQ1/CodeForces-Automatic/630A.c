#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    // PRE: n should be in the range [2, 2 * 10^18]
    int n;
    scanf("%lld", &n);
    assert(n >= 2 && n <= 2000000000000000000); // PRE: n is within the specified range

    printf("25\n");

    // POST: Output should always be "25" for any valid n
    assert(1); // POST: The output is guaranteed to be "25"
    
    return 0;
}