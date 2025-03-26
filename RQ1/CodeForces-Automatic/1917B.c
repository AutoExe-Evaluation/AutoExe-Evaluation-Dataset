#include <stdio.h>
#include <string.h>
#include <assert.h>

long long ans;
char s[100001];
int found[26];

int main() {
    long long TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TC--) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 10^5
        scanf("%s", s);
        
        memset(found, 0, sizeof(found));
        ans = 0;
        for (long long i = 0; i < n; ++i) {
            if (!found[s[i] - 'a']) {
                found[s[i] - 'a'] = 1;
                ans += n - i;
            }
        }
        printf("%lld\n", ans);
        assert(ans > 0); // POST: The number of distinct non-empty strings is positive
    }
    return 0;
}