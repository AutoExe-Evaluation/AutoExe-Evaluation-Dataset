#include <stdio.h>
#include <assert.h>

int main()
{
    int k, n, w;
    scanf("%d %d %d", &k, &n, &w);
    
    assert(k > 0 && w > 0); // PRE: k and w should be positive
    assert(n >= 0); // PRE: n should be non-negative

    int i, money = 0;
    for (i = 1; i <= w; i++)
    {
        money += i * k;
    }

    int borrow = (money > n) ? (money - n) : 0;
    printf("%d\n", borrow);

    assert(borrow >= 0); // POST: borrow should be non-negative
    assert(borrow == (money - n) ? money > n : money <= n); // POST: borrow is correctly calculated based on money and n
}