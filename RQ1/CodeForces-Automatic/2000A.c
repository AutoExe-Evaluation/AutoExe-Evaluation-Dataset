#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: The number of integers must be within the limits
    for (int TC = 1; TC <= TCS; ++TC) {
        char s[12];
        scanf("%s", s);
        int len = strlen(s);
        assert(len <= 10); // PRE: The maximum length of the integer string should be 10
        if (len < 3) {
            printf("NO\n");
        } else if (s[0] == '1' && s[1] == '0') {
            if (s[2] == '0') {
                printf("NO\n");
            } else {
                int n = atoi(s + 2);
                printf(n > 1 ? "YES\n" : "NO\n");
            }
        } else {
            printf("NO\n");
        }
    }
    // POST: The outputs must be either "YES" or "NO" for each integer
    return 0;
}