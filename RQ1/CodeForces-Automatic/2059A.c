#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 50

int main() {
    int TCS;
    scanf("%d", &TCS); 
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= TCS <= 1000

    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 3 && n <= 50); // PRE: 3 <= n <= 50
        int a[MAX_SIZE], b[MAX_SIZE];

        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: 1 <= a[i] <= 10^9
        }

        for (int i = 0; i < n; ++i) {
            scanf("%d", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: 1 <= b[i] <= 10^9
        }

        int st[200] = {0};
        int distinct_count = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int sum = a[i] + b[j];
                if (st[sum] == 0) {
                    st[sum] = 1;
                    distinct_count++;
                }
                if (distinct_count > 2) {
                    printf("YES\n");
                    assert(distinct_count >= 3); // POST: distinct_count >= 3
                    break;
                }
            }
            if (distinct_count > 2) break; // Early break if we already know the result
        }
        
        if (distinct_count <= 2) {
            printf("NO\n");
            assert(distinct_count <= 2); // POST: distinct_count <= 2
        }
    }

    return 0;
}