#include <stdio.h>
#include <assert.h>

int main()
{
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100); // PRE: 1 ≤ n ≤ 100

    int p[101] = {0};
    
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        assert(x >= 1 && x <= n); // Ensure the received friend number is valid
        p[x] = i;
    }
    
    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", p[i]);
    }
    printf("\n");
    
    for (int i = 1; i <= n; ++i)
    {
        assert(p[i] >= 1 && p[i] <= n); // POST: Each friend receives a valid gift from a friend
    }

    return 0;
}