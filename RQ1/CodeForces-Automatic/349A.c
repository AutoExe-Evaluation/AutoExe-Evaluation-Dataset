#include <stdio.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100000); // PRE: n is within the defined bounds
    int hand25 = 0;
    int hand50 = 0;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        assert(x == 25 || x == 50 || x == 100); // PRE: each bill is one of the specified denominations
        if (x == 25) {
            hand25++;
        } else if (x == 50) {
            hand50++;
            hand25--;
            if (hand25 < 0) {
                printf("NO\n");
                return 0;
            }
        } else if (x == 100) {
            if (hand50) {
                hand50--;
                hand25--;
            } else {
                hand25 -= 3;
            }
            if (hand25 < 0) {
                printf("NO\n");
                return 0;
            }
        }
    }
    printf("YES\n");
    assert(hand25 >= 0); // POST: if "YES" is printed, the clerk can provide change
    return 0;
}