#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int t;
    scanf("%d", &t);
    assert(t >= 1 && t <= 1000); // PRE: Number of test cases should be in range [1, 1000]
    
    while (t--) {
        int n, m, k, H;
        scanf("%d %d %d %d", &n, &m, &k, &H);
        assert(n >= 1 && n <= 50); // PRE: Number of people should be in range [1, 50]
        assert(m >= 1 && m <= 50); // PRE: Number of steps should be in range [1, 50]
        assert(k >= 1 && k <= 1000000); // PRE: k should be in range [1, 10^6]
        assert(H >= 1 && H <= 1000000); // PRE: H should be in range [1, 10^6]
        
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000); // PRE: Each person's height should be in range [1, 10^6]
        }
        
        int ct = 0;
        for (int i = 0; i < n; ++i) {
            int d = abs(H - v[i]);
            if (d <= (m - 1) * k && d % k == 0 && v[i] != H) {
                ct++;
            }
        }
        
        printf("%d\n", ct);
        free(v);
        assert(ct >= 0 && ct <= n); // POST: Count of people can only be between 0 and n
    }
    
    return 0;
}