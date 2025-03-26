#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ll long long

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases (TC) should be between 1 and 100.
    
    while (TC--) {
        ll n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 100000); // PRE: Maximum segments (n) should be between 2 and 100,000.
        
        char s[100005];
        int index = 0;
        
        if(n % 2) {
            s[index++] = '7';
            int m = n / 2 - 1;
            for(int i = 0; i < m; i++)
                s[index++] = '1';
        } else {
            int m = n / 2;
            for(int i = 0; i < m; i++)
                s[index++] = '1';
        }
        s[index] = '\0';
        printf("%s\n", s);
        
        assert(index <= n); // POST: The number of characters in the output string should not exceed the number of segments (n).
    }
    return 0;
}