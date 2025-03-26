#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int n;
    scanf("%lld", &n);
    
    assert(n >= 1 && n <= 100); // PRE: 1 ≤ n ≤ 100

    if(n == 1)
    {
        printf("-1\n");
        return 0;
    }
    if(n & 1)
        n--;
    
    printf("%lld %lld\n", n, 2);

    assert(n >= 2 && n <= 100); // POST: 1 < a, b ≤ x and b divides a, a * b > x, a/b < x
    return 0;
}