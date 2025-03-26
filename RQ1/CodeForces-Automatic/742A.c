#include <stdio.h>
#include <assert.h>

int main() {
    long long n;
    scanf("%lld", &n);
    
    assert(n >= 0 && n <= 1000000000) // PRE: n is within the range [0, 10^9]
    
    if (n == 0)
        printf("1\n");
    else if (n % 4 == 1)
        printf("8\n");
    else if (n % 4 == 2)
        printf("4\n");
    else if (n % 4 == 3)
        printf("2\n");
    else
        printf("6\n");

    assert(n == 0 || n % 4 == 0 || n % 4 == 1 || n % 4 == 2 || n % 4 == 3) // POST: last digit is one of {1, 2, 4, 6, 8} based on n
    return 0;
}