#include <stdio.h>
#include <assert.h>

int main() {
    long long n, m, a, len, wid;
    
    scanf("%lld %lld %lld", &n, &m, &a);
    
    assert(n > 0 && m > 0 && a > 0); // PRE: n, m, a should be positive integers

    len = (n + a - 1) / a;
    wid = (m + a - 1) / a;

    long long div = len * wid;

    assert(div >= (n / a) * (m / a)); // POST: div should cover at least the area of the Square
    printf("%lld", div);
    
    return 0;
}
