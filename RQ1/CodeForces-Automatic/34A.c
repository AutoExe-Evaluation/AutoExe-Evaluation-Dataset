#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 2 && n <= 100); // PRE: number of soldiers should be in range [2, 100]
    
    int *v = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
        assert(v[i] >= 1 && v[i] <= 1000); // PRE: soldier height should be in range [1, 1000]
    }
    
    int d = abs(v[0] - v[n-1]);
    int x = 1, y = n;
    for(int i = 1; i < n; i++) {
        int c = abs(v[i] - v[i-1]);
        if(c < d) {
            d = c;
            x = i + 1;
            y = i + 2;
        }
    }
    printf("%d %d\n", x, y > n ? 1 : y);
    
    // POST: x and y should be indices of neighboring soldiers with minimal height difference
    assert(abs(v[x-1] - v[y-1]) == d); // POST: minimal height difference
    free(v);
    
    return 0;
}