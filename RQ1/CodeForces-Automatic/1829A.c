#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int i, t, count;
    char s[11];
    char c[] = "codeforces";
    
    scanf("%d", &t);
    assert(t >= 1 && t <= 1000); // PRE: 1 <= t <= 1000
    while (t--) {
        scanf("%s", s);
        assert(strlen(s) == 10); // PRE: s has length 10
        count = 0;
        for (i = 0; i < 10; i++) {
            if (s[i] != c[i]) {
                count++;
            }
        }
        printf("%d\n", count);
        assert(count >= 0 && count <= 10); // POST: count is in the range [0, 10]
    }
    return 0;
}