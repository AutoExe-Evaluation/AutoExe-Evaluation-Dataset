#include <stdio.h>
#include <assert.h>

int main() {
    int n, cubes = 0;
    scanf("%d", &n);
    assert(n >= 1 && n <= 10000); // PRE: n is in the range [1, 10000]

    for (int i = 1; i <= n; ++i) {
        cubes += (i * i + i) / 2;
        if (cubes > n) {
            printf("%d\n", i - 1);
            assert(cubes - (i * i + i) / 2 <= n); // POST: the number of cubes used does not exceed n
            break;
        } else if (cubes == n) {
            printf("%d\n", i);
            assert(cubes == n); // POST: the number of cubes used is exactly n
            break;
        }
    }
    return 0;
}