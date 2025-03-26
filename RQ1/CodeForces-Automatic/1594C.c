#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

int main() {
    // PRE: The input consists of valid integers and characters as per the problem's constraints.
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be in range [1, 10^4]

    while (TCS--) {
        int n;
        char c;
        char s[300001];
        scanf("%d %c", &n, &c);
        scanf("%s", s);
        assert(n >= 3 && n <= 300000); // PRE: n should be in range [3, 3 * 10^5]

        bool same = true;
        for (int i = 0; i < n; i++) {
            if (s[i] != c) {
                same = false;
                break;
            }
        }
        
        if (same) {
            printf("0\n");
            assert(strcmp(s, &c) == 0); // POST: All characters already equal to c
            continue;
        }

        for (int i = 1; i <= n; i++) {
            bool valid = true;
            for (int j = i; j <= n; j += i) {
                if (s[j - 1] != c) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                printf("1\n%d\n", i);
                assert(i >= 1 && i <= n); // POST: Valid x found
                return 0;
            }
        }

        printf("2\n%d %d\n", n, n - 1);
        assert(n >= 3 && n <= 300000); // POST: x values are valid
    }
    return 0;
}