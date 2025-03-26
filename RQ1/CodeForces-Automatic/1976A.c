#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases is within the valid range

    while(TCS--) {
        int n;
        char s[21];
        scanf("%d %s", &n, s);
        assert(n >= 1 && n <= 20); // PRE: Length of the password is within the valid range

        for(int i = 1; i < n; ++i)
        {
            // Check if characters are sorted
            assert(((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z'))); // PRE: All characters are valid

            if(s[i] < s[i-1])
            {
                printf("NO\n");
                break;
            }
            // Check for digits after letters
            if(('0' <= s[i-1] && s[i-1] <= '9') && ('a' <= s[i] && s[i] <= 'z'))
            {
                printf("NO\n");
                break;
            }
        }
        printf("YES\n"); // POST: Password is strong if no conditions to print "NO" were met.
    }
    return 0;
}