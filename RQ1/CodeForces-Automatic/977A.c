#include <stdio.h>
#include <assert.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    assert(n >= 2 && n <= 1000000000); // PRE: n is within limits
    assert(k >= 1 && k <= 50); // PRE: k is within limits

    while (k--) {
        if (n % 10 == 0) n = n / 10;
        else n = n - 1;
    }

    assert(n > 0); // POST: Result is a positive integer
    printf("%d", n);
    return 0;
}