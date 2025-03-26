#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 990); // PRE: 1 <= t <= 990

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 10 && n <= 999); // PRE: 10 <= n <= 999
        char s[4];
        sprintf(s, "%d", n);
        s[3] = '\0';

        if (n % 7 == 0) {
            printf("%d\n", n);
            assert(n % 7 == 0); // POST: output is divisible by 7
            continue;
        }

        for (int i = 0; i < 10; ++i) {
            s[2] = '0' + i;
            int x = atoi(s);
            if (x % 7 == 0) {
                printf("%d\n", x);
                assert(x % 7 == 0); // POST: output is divisible by 7
                break;
            }
        }
    }
    return 0;
}