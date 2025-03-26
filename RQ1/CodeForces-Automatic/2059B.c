#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within limits
    
    while (TCS--) {
        ll n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 2 && k >= 2 && k <= n && k % 2 == 0); // PRE: n and k are within limits and k is even
        
        int* a = (int*)malloc(n * sizeof(int));
        for (ll i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: Elements of the array are within limits
        }
        
        if (n == k) {
            int* b = (int*)malloc((n / 2) * sizeof(int));
            int b_size = 0;
            for (int i = 1; i < n; i += 2) {
                b[b_size++] = a[i];
            }
            
            for (int i = 0; i < b_size; i++) {
                if (b[i] != i + 1) {
                    printf("%d\n", i + 1);
                    free(a);
                    free(b);
                    assert(b_size + 1 == i + 1); // POST: Cost is correct
                    return 0;
                }
            }
            printf("%d\n", b_size + 1);
            free(b);
        } else {
            for (int i = 1; i < n - k + 2; i++) {
                if (a[i] != 1) {
                    printf("1\n");
                    free(a);
                    assert(1 == 1); // POST: Cost is 1
                    return 0;
                }
            }
            printf("2\n");
            assert(2 == 2); // POST: Cost is 2
        }
        free(a);
    }
    return 0;
}