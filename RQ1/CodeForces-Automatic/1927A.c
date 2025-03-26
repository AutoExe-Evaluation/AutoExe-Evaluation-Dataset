#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases should be in range [1, 10^4]
    
    while (TC--) {
        int n;
        char s[11];
        scanf("%lld %s", &n, s);
        
        assert(n >= 1 && n <= 10); // PRE: length of the strip should be in range [1, 10]
        assert(strspn(s, "WB") == n); // PRE: string should contain only 'W' and 'B'

        int i = 0, j = n - 1;
        while (s[i] == 'W')
            i++;
        while (s[j] == 'W')
            j--;
        
        int result = j - i + 1;
        printf("%lld\n", result);
        
        assert(result > 0); // POST: the result length must be greater than 0 as there is at least one 'B'
    }
    
    return 0;
}