#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases should be in the range [1, 1000]
    
    for (long long TC = 1; TC <= TCS; ++TC) {
        long long n, k;
        scanf("%lld %lld", &n, &k);
        
        assert(n >= 1 && n <= 50); // PRE: Number of chests should be in the range [1, 50]
        assert(k >= 1 && k <= 10000000); // PRE: k should be in the range [1, 10^7]
        
        long long *v = (long long *)malloc(n * sizeof(long long));
        for (long long i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= k); // PRE: Each chest should contain between 1 and k coins
        }
        
        // Sort in descending order
        for (long long i = 0; i < n - 1; i++) {
            for (long long j = 0; j < n - i - 1; j++) {
                if (v[j] < v[j + 1]) {
                    long long temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
        
        long long sum = 0;
        for (long long i = 0; i < n; i++) {
            if (sum + v[i] > k) {
                printf("%lld\n", k - sum);
                free(v);
                assert(sum + v[i] == k); // POST: The sum of coins taken should equal k
                return 0;
            }
            sum += v[i];
        }
        printf("%lld\n", k - sum);
        free(v);
        assert(sum == k); // POST: The total coins should be exactly k after adding
    }
    
    return 0;
}