#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ll long long

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is within bounds
    while (TC--) {
        char s[200001];
        scanf("%s", s);
        assert(strlen(s) >= 2 && strlen(s) <= 200000); // PRE: String length is within bounds
        
        ll ans = 0, ct = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            if (s[i] == '1')
                ct++;
            else if (s[i] == '0' && ct)
                ans += ct + 1;
        }
        
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: Cost must be non-negative
    }
    return 0;
}