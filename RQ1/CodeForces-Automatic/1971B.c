#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= t <= 1000
    while (TCS--) {
        char s[11];
        scanf("%s", s);
        assert(strlen(s) <= 10); // PRE: length of s <= 10
        int len = strlen(s);
        int ok = 0;
        for (int i = 1; i < len; ++i) {
            if (s[i] != s[0]) {
                char temp = s[i];
                s[i] = s[0];
                s[0] = temp;
                ok = 1;
                break;
            }
        }
        if (ok) {
            printf("YES\n%s\n", s);
            assert(strcmp(s, s) != 0); // POST: r is not equal to s
        } else {
            printf("NO\n");
            assert(strcmp(s, s) == 0); // POST: r is equal to s
        }
    }
    return 0;
}