#include <stdio.h>
#include <assert.h>

int main()
{
    int i, n, k, count = 0;
    scanf("%d %d", &n, &k);
    assert(n >= k); // PRE: n must be greater than or equal to k
    int s[50];
    for (i = 0; i < n; i++)
    {
        scanf("%d", &s[i]);
    }
    assert(s[k - 1] >= 0); // PRE: the k-th place score must be non-negative
    for (i = 0; i < n; i++)
    {
        if (s[i] > 0 && s[i] >= s[k - 1])
        {
            count++;
        }
    }
    printf("%d", count);
    assert(count >= 0); // POST: the count of participants who advance must be non-negative
    return 0;
}