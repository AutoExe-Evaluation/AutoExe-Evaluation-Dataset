#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases within valid range

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100); // PRE: Number of cells within valid range
        char s[101];
        scanf("%s", s);
        
        int cnt = 0, ct = 0, mx = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == '.') {    
                cnt++;
                ct++;
            }
            if (s[i] == '#') {
                if (ct > mx) mx = ct;
                ct = 0;
            }  
        }
        if (ct > mx) mx = ct;

        // Ensure that the postcondition reflects the minimum actions needed
        assert(cnt == 0 || (mx <= 2 ? cnt : 2) >= 0); // POST: Minimum actions calculated correctly
        if (cnt == 0)
            printf("0\n");
        else if (mx > 2)
            printf("2\n");
        else 
            printf("%lld\n", cnt);
    }
    return 0;
}