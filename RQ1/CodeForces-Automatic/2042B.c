#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int key;
    int value;
} Pair;

int compare(const void *a, const void *b) {
    return ((Pair*)a)->key - ((Pair*)b)->key;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= t <= 1000
    for (int TC = 1; TC <= TCS; ++TC) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 1000); // PRE: 1 <= n <= 1000

        Pair *m = (Pair*)malloc(n * sizeof(Pair));
        int size = 0;

        for(int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= n); // PRE: 1 <= c_i <= n
            int found = 0;
            for(int j = 0; j < size; j++) {
                if(m[j].key == x) {
                    m[j].value++;
                    found = 1;
                    break;
                }
            }
            if(!found) {
                m[size].key = x;
                m[size].value = 1;
                size++;
            }
        }
        
        int ct1 = 0, ct2 = 0;
        for(int i = 0; i < size; i++) {
            if(m[i].value == 1)
                ct1++;
            else if(m[i].value > 1)
                ct2++;
        }
        
        int score = ct2 + 2 * ((ct1 + 1) / 2);
        printf("%d\n", score); 
        free(m);
        assert(score >= 0); // POST: Alice's score should be non-negative
    }
    return 0;
}