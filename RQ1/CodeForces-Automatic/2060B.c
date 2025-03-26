#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp(const void *a, const void *b) {
    return (*(long long*)a - *(long long*)b);
}

int main() {
    long long TCS;
    
    // PRE: Number of test cases t (1 ≤ t ≤ 400)
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 400); // PRE: Valid number of test cases

    for (long long TC = 1; TC <= TCS; ++TC) {
        long long n, m;
        scanf("%lld %lld", &n, &m);
        assert(n * m <= 2000); // PRE: Total number of cards <= 2000
        long long **cards = malloc(n * sizeof(long long *));
        long long *index = malloc(n * sizeof(long long));
        
        for (long long i = 0; i < n; ++i) {
            cards[i] = malloc(m * sizeof(long long));
            for (long long j = 0; j < m; ++j) {
                scanf("%lld", &cards[i][j]);
                assert(cards[i][j] >= 0 && cards[i][j] < n * m); // PRE: Card within valid range
            }
            qsort(cards[i], m, sizeof(long long), cmp);
            index[i] = i + 1;
        }

        long long prev = -1;
        int possible = 1;

        for (long long j = 0; j < m; ++j) {
            for (long long i = 0; i < n; ++i) {
                if (prev > cards[i][j]) {
                    possible = 0; // Not possible to play all cards
                    break;
                }
                prev = cards[i][j];
            }
            if (!possible) break;
        }
        
        if (!possible) {
            printf("-1\n");
        } else {
            for (long long i = 0; i < n; ++i) {
                printf("%lld ", index[i]);
            }
            printf("\n");
        }

        for (long long i = 0; i < n; ++i) {
            free(cards[i]);
        }
        free(cards);
        free(index);
    }
    
    // POST: The output has correctly displayed a valid permutation or -1
    return 0;
}