#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int TCS = 0;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases is within limits

    for (int TC = 0; TC < TCS; TC++) {
        int n, f, k;
        scanf("%d %d %d", &n, &f, &k);
        assert(n >= 1 && n <= 100); // PRE: n is within limits
        assert(f >= 1 && f <= n); // PRE: f index is valid
        assert(k >= 1 && k <= n); // PRE: k is within limits

        int *v = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 100); // PRE: values are within limits
        }
        int fav = v[f - 1];
        qsort(v, n, sizeof(int), cmp);
        
        if (k == n || v[k] < fav) {
            printf("YES\n");
        } else if (v[k] == fav && v[k - 1] == fav) {
            printf("MAYBE\n");
        } else {
            printf("NO\n");
        }
        
        free(v);
        
        // POST: Output is determined according to the favorite cube's position
        assert(k == n || v[k] < fav || (v[k] == fav && v[k - 1] == fav) || (fav != v[k] && fav != v[k - 1])); // POST: Valid output conditions
    }
    
    return 0;
}