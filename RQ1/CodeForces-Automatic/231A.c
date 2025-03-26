#include <stdio.h>
#include <assert.h>

int main() {
    int n, i, sum, count = 0;
    int p[3];
    scanf("%d", &n);
    assert(n >= 1 && n <= 1000); // PRE: Number of problems must be between 1 and 1000
    while (n--) {
        sum = 0;
        for (i = 0; i < 3; i++) {
            scanf("%d", &p[i]);
            assert(p[i] == 0 || p[i] == 1); // PRE: Each friend must either be sure (1) or not sure (0)
            sum += p[i];
        }
        if (sum >= 2) count++;
    }
    printf("%d", count);
    assert(count >= 0 && count <= 1000); // POST: The number of problems implemented must be non-negative and cannot exceed n
    return 0;
}