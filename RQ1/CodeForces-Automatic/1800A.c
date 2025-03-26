#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: 1 ≤ n ≤ 50
        char s[51];
        scanf("%s", s);

        char sound[51] = "";
        int idx = 0;

        for (int i = 0; i < n; ++i) {
            s[i] = tolower(s[i]);
            if (idx == 0 || sound[idx - 1] != s[i]) {
                sound[idx++] = s[i];
            }
        }
        sound[idx] = '\0';

        // Check if the sound matches "meow"
        if (strcmp(sound, "meow") == 0) {
            printf("YES\n");
            assert(1); // POST: Output is "YES"
        } else {
            printf("NO\n");
            assert(0); // POST: Output is "NO"
        }
    }
    return 0;
}