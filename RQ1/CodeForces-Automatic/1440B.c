#include <stdio.h>
#include <assert.h>

long long v[200000];

int main() {
    int TCS;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases must be within the range [1, 100]
    
    while (TCS--) {
        long long n, k;
        scanf("%lld %lld", &n, &k);
        
        assert(n >= 1 && n <= 1000); // PRE: n must be within the range [1, 1000]
        assert(k >= 1 && k <= 1000); // PRE: k must be within the range [1, 1000]

        long long range = n * k, j = 0, div = 0, sum = 0;
        div = n / 2;

        for (long long i = 0; i < range; i++) {
            scanf("%lld", &v[i]);
        }

        for (long long i = range - 1 - div; i >= 0; i -= div + 1) {
            sum += v[i];
            j++;
            if (j == k) break;
        }

        printf("%lld\n", sum);
        assert(sum >= 0); // POST: The sum of medians must be non-negative
    }
    
    return 0;
}