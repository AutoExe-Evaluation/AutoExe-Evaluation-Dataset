#include <stdio.h>
#include <assert.h>

int main()
{
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases is within bounds

    while (TC--) {
        int n, k, x;
        scanf("%d %d %d", &n, &k, &x);
        assert(n >= 1 && n <= 200); // PRE: n is within bounds
        assert(k >= 1 && k <= 200); // PRE: k is within bounds
        assert(x >= 1 && x <= 200); // PRE: x is within bounds

        if (n < k || x + 1 < k) {
            printf("-1\n");
            continue;
        }
        
        int i = 0, ct = 0, sum = 0;
        while (i < k && ct < n) {
            sum += i;
            i++;
            ct++;
        }
        if (ct < n) {
            if (x != k) {
                while (ct < n) {
                    sum += x;
                    ct++;
                }
            } else if (x == k) {
                x--;
                while (ct < n) {
                    sum += x;
                    ct++;
                }
            }
        }

        printf("%d\n", sum);
        assert(sum >= 0); // POST: The sum of elements is non-negative
    }
    
    return 0;
}