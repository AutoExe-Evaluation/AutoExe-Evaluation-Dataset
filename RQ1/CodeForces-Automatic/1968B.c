#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_SIZE 200000

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be within the valid range
    while (TCS--) {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 200000); // PRE: Length of string a should be within the valid range
        assert(m >= 1 && m <= 200000); // PRE: Length of string b should be within the valid range
        
        char a[MAX_SIZE + 1], b[MAX_SIZE + 1];
        scanf("%s", a);
        scanf("%s", b);
        
        int ans = 0;
        for (int i = 0, j = 0; i < n && j < m; ++j) {
            if (a[i] == b[j]) {
                ans++;
                i++;
            }
        }
        printf("%d\n", ans);
        assert(ans >= 0 && ans <= n); // POST: The answer should be a valid count of prefixes forming a subsequence
    }
    return 0;
}