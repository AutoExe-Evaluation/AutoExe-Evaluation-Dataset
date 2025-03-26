#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXN 200005

long long a[MAXN];

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10^4
    while (TCS--) {
        int n, m;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
        }
        scanf("%d", &m);
        assert(m >= 1 && m <= 200000); // PRE: 1 <= m <= 2 * 10^5
        while (m--) {
            char s[MAXN];
            scanf("%s", s);
            assert(strlen(s) == n); // PRE: length of s must equal n
            int char_to_num[26] = {0};
            int num_to_char[MAXN] = {0};
            int f = 1;
            for (int j = 0; j < n; ++j) {
                char c = s[j];
                int num = a[j];
                if (char_to_num[c - 'a'] != 0 && char_to_num[c - 'a'] != num + 1) {
                    f = 0;
                    break;
                }
                if (num_to_char[num + 100000] != 0 && num_to_char[num + 100000] != c) {
                    f = 0;
                    break;
                }
                char_to_num[c - 'a'] = num + 1;
                num_to_char[num + 100000] = c;
            }
            printf(f ? "YES\n" : "NO\n");
            assert((f && strcmp(f ? "YES" : "NO", "YES") == 0) || (!f && strcmp(f ? "YES" : "NO", "NO") == 0)); // POST: Correctly determined if s matches template
        }
    }
    return 0;
}