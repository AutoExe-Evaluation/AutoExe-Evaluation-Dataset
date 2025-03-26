#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

typedef long long ll;

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4
    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 3 && n <= 100000); // PRE: 3 ≤ n ≤ 10^5
        char s[100001];
        scanf("%s", s);
        int mp[26] = {0}; // for lowercase letters a to z

        for (int i = 0; i < n; ++i) {
            mp[s[i] - 'a']++;
        }
        
        int found = 0; // To track if a valid configuration is found
        for (int i = 1; i < n - 1; ++i) {
            if (mp[s[i] - 'a'] > 1) {
                found = 1;
                break;
            }
        }
        
        if (found) {
            printf("YES\n");
            assert(n > 1); // POST: existence of a, b, c such that conditions hold
        } else {
            printf("NO\n");
            assert(n > 1); // POST: no valid configuration found
        }
    }
    return 0;
}