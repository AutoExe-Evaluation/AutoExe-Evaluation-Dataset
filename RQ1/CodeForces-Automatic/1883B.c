#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    long long TC;
    scanf("%lld", &TC); // PRE: TC > 0
    assert(TC > 0); // POST: TC > 0
    while (TC--) {
        long long n, k;
        scanf("%lld %lld", &n, &k); // PRE: 0 <= k < n <= 100000
        assert(0 <= k && k < n && n <= 100000); // POST: 0 <= k < n <= 100000
        char s[100001];
        scanf("%s", s); // PRE: strlen(s) == n
        assert(strlen(s) == n); // POST: strlen(s) == n
        long long m[26] = {0};
        for (long long i = 0; i < n; i++) {
            m[s[i] - 'a']++;
        }
        long long odd = 0;
        for (long long i = 0; i < 26; i++) {
            if (m[i] % 2)
                odd++;
        }
        if (n - k == 0 || odd > k + 1)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}