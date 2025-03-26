#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 100); // PRE: number of test cases is within limits

    while (t--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 500); // PRE: duration of the contest is within limits

        char s[501];
        scanf("%s", s);
        assert(strlen(s) == n); // PRE: length of the log matches duration

        int cnt[26] = {0};
        for (int i = 0; i < n; ++i) {
            cnt[s[i] - 'A']++;
        }
        int ct = 0;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] >= i + 1) {
                ct++;
            }
        }
        printf("%lld\n", ct);
        assert(ct >= 0 && ct <= 26); // POST: number of problems solved is within valid range
    }
    return 0;
}