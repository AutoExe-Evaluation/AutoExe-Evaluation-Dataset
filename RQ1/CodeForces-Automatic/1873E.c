#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int check(long long *v, int n, long long x, long long h) {
    long long s = 0;
    for(int i = 0; i < n; ++i) {
        s += max(h - v[i], 0);
    }
    return s <= x;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases within limits
    while (TCS--) {
        int n;
        long long x;
        scanf("%d %lld", &n, &x);
        assert(n >= 1 && n <= 200000); // PRE: Number of columns within limits
        assert(x >= 1 && x <= 1000000000); // PRE: Maximum water within limits
        
        long long *v = (long long *)malloc(n * sizeof(long long));
        for(int i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: Coral heights within limits
        }
        
        long long low = 0, high = 1e10;
        while (low < high) {
            long long mid = low + (high - low + 1) / 2;
            if (check(v, n, x, mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        printf("%lld\n", low);
        free(v);
        assert(low >= 1); // POST: Maximum height is at least 1
    }
    return 0;
}