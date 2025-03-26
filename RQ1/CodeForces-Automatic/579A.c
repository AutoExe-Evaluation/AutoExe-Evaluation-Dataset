#include <stdio.h>
#include <assert.h>

int main() {
    long long x;
    scanf("%lld", &x);
    assert(x >= 1 && x <= 1000000000); // PRE: x is in the range [1, 10^9]

    int count = 0;
    while (x > 0) {
        count += (x & 1);
        x >>= 1;
    }
    
    printf("%d\n", count);
    assert(count >= 1); // POST: Count of bacteria needed is at least 1
    return 0;
}