#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases is within bounds

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 40); // PRE: Length of the array is within bounds

        int odd_ct = 0, even_ct = 0;

        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            assert(x >= 0 && x <= 1000); // PRE: Array elements are within bounds

            if (i % 2 == 0 && x % 2 != 0)
                even_ct++;
            else if (i % 2 != 0 && x % 2 == 0)
                odd_ct++;
        }

        if (odd_ct != even_ct) {
            printf("-1\n");
            assert(odd_ct == even_ct || odd_ct + even_ct == n); // POST: Either can be fixed or impossible
        } else {
            printf("%d\n", odd_ct);
            assert(odd_ct == even_ct); // POST: The array can be made good
        }
    }
    return 0;
}