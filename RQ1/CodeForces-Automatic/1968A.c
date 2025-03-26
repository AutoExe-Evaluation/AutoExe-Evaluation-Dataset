#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= TCS <= 1000

    for (int TC = 1; TC <= TCS; ++TC)
    {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 1000); // PRE: 2 <= n <= 1000
        printf("%d\n", n - 1);
        assert((n - 1) >= 1 && (n - 1) < n); // POST: 1 <= y < n
    }
    return 0;
}