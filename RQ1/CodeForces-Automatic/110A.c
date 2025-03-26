#include <stdio.h>
#include <assert.h>

int main() {
    long long n;
    int count = 0;

    scanf("%lld", &n);
    assert(n >= 1 && n <= 1000000000000000000LL); // PRE: 1 ≤ n ≤ 10^18

    while (n != 0) {
        if (n % 10 == 4 || n % 10 == 7) count++;
        n = n / 10;
    }
    
    assert(count >= 0); // POST: count is non-negative
    if (count == 4 || count == 7) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    assert(count == 4 || count == 7 || (count != 4 && count != 7 && (n >= 1 && n <= 1000000000000000000LL))); // POST: Output is consistent with the definition
    return 0;
}