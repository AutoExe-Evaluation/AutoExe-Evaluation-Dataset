#include <stdio.h>
#include <assert.h>

int main() {
    int n, count = 0;
    scanf("%d", &n);
    assert(n >= 1 && n <= 1000000); // PRE: input x must be in the range 1 to 1000000

    if (n % 5)
        printf("%d\n", n / 5 + 1);
    else
        printf("%d\n", n / 5);
    
    assert(n / 5 + (n % 5 > 0 ? 1 : 0) == (n + 4) / 5); // POST: the output is the minimum steps to reach point x
    return 0;
}