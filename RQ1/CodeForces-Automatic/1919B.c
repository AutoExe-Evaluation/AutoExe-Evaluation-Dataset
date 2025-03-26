#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TC, n, ans;
    char s[5001];

    scanf("%d", &TC); // PRE: TC >= 1 && TC <= 1000
    assert(TC >= 1 && TC <= 1000);
    
    while (TC--) {
        scanf("%d", &n); // PRE: n >= 1 && n <= 5000
        assert(n >= 1 && n <= 5000);
        
        scanf("%s", s); // PRE: strlen(s) == n && s[i] in {'+', '-'}
        assert(strlen(s) == n);

        ans = 0; // Initialize the penalty
        for (int i = 0; i < n; i++) {
            if (s[i] == '+')
                ans++;
            else
                ans--;
        }
        printf("%lld\n", abs(ans)); // POST: ans is the minimum possible penalty
        assert(abs(ans) >= 0); // should be non-negative
    }
    return 0;
}