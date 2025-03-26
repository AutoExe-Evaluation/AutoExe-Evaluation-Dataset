#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases is valid
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 200000 && n % 2 == 0); // PRE: n is a valid even positive integer
        int v[200000];
        if (n % 4 != 0) {
            printf("NO\n");
        } else {
            int even_sum = 0;
            int odd_sum = 0;
            int ct = 0;
            for (int i = 2; i <= n; i += 2) {
                v[ct++] = i;
                even_sum += i;
            }
            for (int i = 1; i < n; i += 2) {
                if (ct == (n / 2) - 1)
                    break;
                v[ct++] = i;
                odd_sum += i;
            }
            v[ct] = even_sum - odd_sum;
            printf("YES\n");
            for (int i = 0; i < n; i++) {
                printf("%d ", v[i]);
            }
            printf("\n");
            assert(even_sum == odd_sum + v[ct]); // POST: sum of first half equals sum of second half
        }
    }
    return 0;
}