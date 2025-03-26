#include <stdio.h>
#include <assert.h>

#define MAXN 1001

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be in the specified range.

    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 1000 && n % 2 == 0); // PRE: n should be even and within specified range.
        
        int v[MAXN] = {0};
        
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= n); // PRE: Each number should be within specified range.
            v[x]++;
        }
        
        for (int i = 1; i <= n; i++) {
            if (v[i] > 2) {
                int have = v[i] - 2;
                v[i] -= have;
                for (int j = i + 1; j <= n; j++) {
                    int ct = v[j];
                    if (ct % 2) {
                        have--;
                        v[j]++;
                        if (have < 1) break;
                    } else {
                        v[j] += have;
                        break;
                    }
                }
            }
        }
        
        for (int i = 1; i <= n; i++) {
            // POST: After processing, all elements in v must be even.
            assert(v[i] % 2 == 0);
            if (v[i] % 2) {
                printf("No\n");
                break;
            }
            if (i == n) {
                printf("Yes\n");
            }
        }
    }
    
    return 0;
}