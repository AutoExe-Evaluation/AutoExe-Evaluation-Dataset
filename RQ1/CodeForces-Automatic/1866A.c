#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    long long n;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 100000); // PRE: n must be in the range [1, 100000]
    
    long long *v = (long long*) malloc(n * sizeof(long long));
    for (long long i = 0; i < n; ++i) {
        long long x;
        scanf("%lld", &x);
        assert(x >= -100000 && x <= 100000); // PRE: A_i must be in the range [-100000, 100000]
        if (x < 0) x = -x;
        v[i] = x;
    }
    
    // Sorting the array using a simple bubble sort
    for (long long i = 0; i < n - 1; i++) {
        for (long long j = i + 1; j < n; j++) {
            if (v[i] > v[j]) {
                long long temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
    
    printf("%lld\n", v[0]);
    assert(v[0] >= 0); // POST: The minimum operations required (v[0]) must be non-negative
    free(v);
    
    return 0;
}