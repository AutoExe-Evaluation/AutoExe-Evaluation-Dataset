#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int t, len;
    char s[101];
    scanf("%d", &t);
    assert(t >= 1 && t <= 100); // PRE: 1 ≤ n ≤ 100

    while(t--) {
        scanf("%s", s);
        len = strlen(s);
        assert(len >= 1 && len <= 100); // PRE: 1 ≤ length of each word ≤ 100
        if(len > 10) {
            printf("%c%d%c\n", s[0], len - 2, s[len - 1]);
        } else {
            printf("%s\n", s);
        }
    }
    
    // POST: Each word is transformed correctly or unchanged if ≤ 10 characters
    return 0;
}