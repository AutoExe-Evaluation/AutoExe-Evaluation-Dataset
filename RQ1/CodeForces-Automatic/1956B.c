#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: TC must be between 1 and 10^4

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: n must be between 1 and 2 * 10^5
        
        int* cards = (int*)calloc(n, sizeof(int));
        int* count = (int*)calloc(n + 1, sizeof(int));

        for(int i = 0; i < n; ++i) {
            scanf("%d", &cards[i]);
            assert(cards[i] >= 1 && cards[i] <= n); // PRE: Card values must be between 1 and n
            count[cards[i]]++;
        }

        int ct = 0;
        for(int i = 1; i <= n; ++i) {
            if(count[i] == 2) ct++;
        }

        printf("%d\n", ct);
        assert(ct >= 0 && ct <= n / 2); // POST: Maximum points can only be up to n/2
        free(cards);
        free(count);
    }
    
    return 0;
}