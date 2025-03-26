#include <stdio.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 2 && n <= 100000); // PRE: 2 ≤ n ≤ 100000
    int b[n], a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    
    int p = 0, q = 0;
    int f = 0;
    for (int i = n - 1; i >= 0; i--) {
        int d = b[i];
        if (f) {
            a[i] = d - p + q;
            p += a[i];
            f = 0;
        } else {
            a[i] = d + p - q;
            q += a[i];
            f = 1;
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    assert(a[0] - a[1] + a[2] - a[3] + ... (the series continues) == b[0]); // POST: Each ai matches the defined series related to bi
    return 0;
}