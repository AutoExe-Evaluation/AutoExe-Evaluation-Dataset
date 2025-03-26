#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int key;
    int value;
} Pair;

int cmp(const void *a, const void *b) {
    return (*(Pair *)a).key - (*(Pair *)b).key;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: number of test cases is within bounds

    while (TCS--) {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(n >= 2 && n <= 200000 && n % 2 == 0); // PRE: n is even and within bounds
        assert(k >= 1 && k <= 2 * n); // PRE: k is within bounds

        int *x = (int *)malloc(n * sizeof(int));
        Pair *cnt = (Pair *)malloc(n * sizeof(Pair));
        int unique_count = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d", &x[i]);
            assert(x[i] >= 1 && x[i] <= n); // PRE: elements are within bounds
            int found = 0;
            for (int j = 0; j < unique_count; j++) {
                if (cnt[j].key == x[i]) {
                    cnt[j].value++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                cnt[unique_count].key = x[i];
                cnt[unique_count].value = 1;
                unique_count++;
            }
        }

        int ans = 0;
        for (int i = 0; i < unique_count; i++) {
            for (int j = 0; j < unique_count; j++) {
                if (cnt[i].key + cnt[j].key == k) {
                    ans += (cnt[i].value < cnt[j].value) ? cnt[i].value : cnt[j].value;
                }
            }
        }

        printf("%d\n", ans / 2);
        free(x);
        free(cnt);
        
        assert(ans >= 0); // POST: score cannot be negative
    }
    
    return 0;
}