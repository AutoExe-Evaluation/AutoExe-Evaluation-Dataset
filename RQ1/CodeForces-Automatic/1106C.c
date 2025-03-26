#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int n;
    scanf("%lld", &n);
    assert(n % 2 == 0 && n >= 2 && n <= 300000); // PRE: n is even and in the range [2, 300000]
    
    int *v = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &v[i]);
        assert(v[i] >= 1 && v[i] <= 10000); // PRE: each a_i is in the range [1, 10000]
    }
    
    // Sort the array
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[i] > v[j]) {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < n / 2; i++) {
        int sum = v[i] + v[n - i - 1];
        sum *= sum;
        ans += sum;
    }
    
    printf("%lld\n", ans);
    free(v);
    
    assert(ans >= 0); // POST: the answer should be non-negative
    return 0;
}