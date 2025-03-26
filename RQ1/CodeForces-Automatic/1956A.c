#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int TC;
    scanf("%d", &TC);
    
    while (TC--) {
        int k, q;
        scanf("%d %d", &k, &q);
        int kick[MAX_SIZE], player[MAX_SIZE];

        for(int i = 0; i < k; i++) {
            scanf("%d", &kick[i]);
        }

        for(int i = 0; i < q; i++) {
            scanf("%d", &player[i]);
        }

        for(int i = 0; i < q; i++) {
            assert(player[i] >= 1 && player[i] <= 100); // PRE: 1 ≤ n_i ≤ 100
            int winners = (kick[0] - 1 < player[i]) ? player[i] : kick[0] - 1;
            assert(winners >= 0 && winners <= player[i]); // POST: Number of winners is valid
            printf("%d ", winners);
        }
        printf("\n");
    }
    return 0;
}