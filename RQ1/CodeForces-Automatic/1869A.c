#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: 1 ≤ t ≤ 500
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 100); // PRE: 2 ≤ n ≤ 100
        int v[100];
        int flag = 1;
        for(int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 0 && v[i] <= 100); // PRE: 0 ≤ a_i ≤ 100
            if (v[i] != 0)
                flag = 0;
        }
        if (flag) {
            printf("0\n");
            assert(flag == 1); // POST: Array already contains all zeros
            continue;
        }
        if (n % 2) {
            printf("4\n");
            printf("1 %d\n", n - 1);
            printf("1 %d\n", n - 1);
            printf("%d %d\n", n - 1, n);
            printf("%d %d\n", n - 1, n);
        } else {
            printf("2\n");
            printf("1 %d\n", n);
            printf("1 %d\n", n);
        }
    }
    return 0;
} // POST: All elements in array are changed to 0