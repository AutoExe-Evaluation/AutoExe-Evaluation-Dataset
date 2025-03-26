#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MOD 1000000007

long long pow(long long x, long long y, long long m) {
    long long ans = 1;
    x %= m;
    while (y) {
        if (y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    assert(t >= 1 && t <= 100000); // PRE: 1 ≤ t ≤ 10^5

    int *a = (int *)malloc(t * sizeof(int));
    int *b = (int *)malloc(t * sizeof(int));

    for(int i = 0; i < t; i++) {
        scanf("%d", &a[i]);
        assert(a[i] >= 2 && a[i] <= 100000); // PRE: 2 ≤ n_i ≤ 10^5
    }
    for(int i = 0; i < t; i++) {
        scanf("%d", &b[i]);
        assert(b[i] >= 1 && b[i] < a[i]); // PRE: 1 ≤ k_i < n_i
    }
    
    for (int i = 0; i < t; i++) {
        int n = a[i];
        int k = b[i];
        long long result;
        if (n == k) result = 1;
        else if (k == 0) result = 0;
        else result = pow(2, k, MOD);
        
        printf("%lld\n", result);
        assert(result >= 0 && result < MOD); // POST: 0 ≤ C[n_i][k_i] < 10^9 + 7
    }
    
    free(a);
    free(b);
    return 0;
}