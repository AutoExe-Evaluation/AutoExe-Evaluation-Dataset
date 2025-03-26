#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        char s[200001];
        scanf("%s", s);
        int n = strlen(s);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= |s| <= 2 * 10^5
        
        int cnt[2] = {0, 0};

        for (int i = 0; i < n; ++i) {
            assert(s[i] == '0' || s[i] == '1'); // PRE: s consists only of '0's and '1's
            cnt[s[i] - '0']++;
        }

        for (int i = 0; i < n; ++i) {
            int x = (s[i] - '0') ^ 1;
            if (cnt[x] == 0) {
                printf("%lld\n", n - i);
                break; // POST: Minimum cost to make t good is printed
            }
            cnt[x]--;
        }
        printf("0\n"); // POST: Depth scenario where no cost is incurred
    }
    return 0;
}