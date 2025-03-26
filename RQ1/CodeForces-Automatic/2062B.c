#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases must be between 1 and 10^4
    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 500000); // PRE: Number of clocks must be between 2 and 5*10^5
        long long* v = (long long*)malloc(n * sizeof(long long));
        long long sum_a = 0; // sum of initial times
        for(int i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: Each clock's time must be between 1 and 10^9
            sum_a += v[i];
        }
        for(int i = 1; i <= n; ++i) {
            long long a = 2 * (i - 1);
            long long b = 2 * (n - i);
            long long mx = max(a, b);
            if(v[i - 1] <= mx) {
                printf("NO\n"); // POST: At least one clock reaches 0
                free(v);
                break;
            }
            if (i == n) {
                printf("YES\n"); // POST: It's possible to continue indefinitely
            }
        }
        free(v);
    }
    return 0;
}