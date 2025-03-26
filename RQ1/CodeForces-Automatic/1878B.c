#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases is valid
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 3 && n <= 200000); // PRE: size of array is valid
        int in = 1, s = 0;
        for (int i = 0; i < n; ++i) {
            printf("%d ", s + in);
            s = s + 2;
        }
        printf("\n");
        assert(n > 0); // POST: size of array is greater than 0
    }
    return 0;
}