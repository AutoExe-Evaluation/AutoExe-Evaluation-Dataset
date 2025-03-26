#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases must be in range [1, 10^4]
    
    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Size of the array must be in range [1, 2 * 10^5]
        
        int* v = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= n); // PRE: Array elements must be in range [1, n]
        }
        
        int i = 0, j = n - 1, left = 0, right = 0;
        while (i < n && v[i] == v[0]) i++, left++;
        while (j >= 0 && v[j] == v[n - 1]) j--, right++;
        
        int result;
        if (v[0] == v[n - 1]) {
            result = (left + right < n) ? n - left - right : 0;
        } else {
            result = (left < n - right) ? left : n - right;
        }
        
        printf("%lld\n", result);
        assert(result >= 0); // POST: Result must be non-negative
        free(v);
    }
    return 0;
}