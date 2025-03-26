#include <stdio.h>
#include <stdlib.h>

#define int long long

int cmp(const void *a, const void *b) {
    return ((*(long long *)b) - (*(long long *)a));
}

int main() {
    int TC;
    scanf("%lld", &TC); // PRE: TC >= 1
    while (TC--) {
        int n;
        scanf("%lld", &n); // PRE: n >= 3
        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));
        int *c = (int *)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) {
            scanf("%lld", &a[i]); // PRE: 1 <= a[i] <= 10^8
        }
        for(int i = 0; i < n; i++) {
            scanf("%lld", &b[i]); // PRE: 1 <= b[i] <= 10^8
        }
        for(int i = 0; i < n; i++) {
            scanf("%lld", &c[i]); // PRE: 1 <= c[i] <= 10^8
        }
        
        int ans = 0;
        for(int i = 0; i < n; i++) {
            long long y1 = -1, y2 = -1, z1 = -1, z2 = -1;
            for(int j = 0; j < n; j++) {
                if(j != i) {
                    if(b[j] > y1) {
                        z2 = z1;
                        y2 = y1;
                        y1 = b[j];
                    } else if(b[j] > y2) {
                        y2 = b[j];
                    }
                    if(c[j] > z1) {
                        z2 = z1;
                        z1 = c[j];
                    } else if(c[j] > z2) {
                        z2 = c[j];
                    }
                }
            }
            if(y1 == z1) {
                ans = (ans > (a[i] + y2 + z2) ? ans : (a[i] + y2 + z2));
            } else {
                ans = (ans > (a[i] + y1 + z1) ? ans : (a[i] + y1 + z1));
            }
        }
        printf("%lld\n", ans); // POST: ans = max(a_x + b_y + c_z) for distinct x, y, z

        free(a);
        free(b);
        free(c);
    }
    return 0;
}