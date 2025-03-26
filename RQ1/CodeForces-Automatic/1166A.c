#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXN 100
#define MAXLEN 20

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100); // PRE: n is between 1 and 100
    int count[26] = {0}; // To count occurrences of first letters

    for (int i = 0; i < n; ++i) {
        char s[MAXLEN + 1];
        scanf("%s", s);
        assert(strlen(s) <= 20); // PRE: Each name is at most 20 characters
        count[s[0] - 'a']++;
    }

    long long ans = 0;
    for (int i = 0; i < 26; ++i) {
        int y = count[i];
        if (y > 1) {
            int c1 = y / 2;
            int c2 = y - c1;
            long long p1 = (long long)c1 * (c1 - 1) / 2;
            long long p2 = (long long)c2 * (c2 - 1) / 2;
            ans += p1 + p2;
        }
    }

    assert(ans >= 0); // POST: The number of chatty pairs must be non-negative
    printf("%lld\n", ans);
    return 0;
}