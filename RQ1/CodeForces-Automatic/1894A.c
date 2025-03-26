#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TC;
    assert(TC > 0);  // PRE: Number of test cases must be greater than 0
    scanf("%d", &TC);
    
    while (TC--) {
        int n;
        char s[21];
        scanf("%d %s", &n, s);
        
        assert(n >= 1 && n <= 20);  // PRE: Number of plays must be between 1 and 20
        assert(strlen(s) == n);  // PRE: Length of string s must match n
        
        char winner = s[n-1];
        printf("%c\n", winner);
        
        assert(winner == 'A' || winner == 'B');  // POST: Winner must be A or B
    }
    
    return 0;
}