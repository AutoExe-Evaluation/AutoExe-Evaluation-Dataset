#include <stdio.h>
#include <assert.h>

int main() {
    long long n, sum = 0;
    
    // PRE: n must be a positive integer (1 ≤ n ≤ 10^15)
    scanf("%lld", &n);
    assert(n >= 1 && n <= 1000000000000000LL); // PRE: 1 ≤ n ≤ 10^15

    if (n % 2 == 0) 
        sum = n / 2;
    else 
        sum = -(n / 2 + 1);

    printf("%lld\n", sum);
    
    // POST: the value of sum should be f(n) defined as -1 + 2 - 3 + ... + (-1)^n * n
    assert((n % 2 == 0 && sum == n / 2) || (n % 2 == 1 && sum == -(n / 2 + 1)); // POST: f(n) is calculated correctly

    return 0;
}