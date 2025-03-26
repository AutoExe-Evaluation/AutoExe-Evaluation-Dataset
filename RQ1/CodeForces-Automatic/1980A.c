#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases should be between 1 and 1000

    while (TCS--) {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 50); // PRE: Number of problems should be between 1 and 50
        assert(m >= 1 && m <= 5);   // PRE: Number of rounds should be between 1 and 5
        
        char s[51];
        scanf("%s", s);

        int v[7] = {0};
        
        for(int i = 0; i < n; i++) {
            v[s[i] - 'A']++;
        }
        
        int ans = 0;
        for(int i = 0; i < 7; i++) {
            if(v[i] < m) {
                ans += (m - v[i]);
            }
        }
        
        printf("%d\n", ans);
        assert(ans >= 0); // POST: The number of problems to come up with should never be negative
    }

    return 0;
}