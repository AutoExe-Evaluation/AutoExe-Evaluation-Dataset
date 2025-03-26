#include <stdio.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    
    assert(n >= 1 && n <= 1000); // PRE: n should be within the specified range
    
    int v[1000];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
        assert(v[i] >= 1 && v[i] <= 1000); // PRE: each element should be within the specified range
    }
    
    int ct = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (v[i] < v[i - 1] && v[i] < v[i + 1]) ct++;
        if (v[i] > v[i - 1] && v[i] > v[i + 1]) ct++;
    }
    
    printf("%d\n", ct);
    assert(ct >= 0); // POST: count of local extrema should be non-negative
    return 0;
}