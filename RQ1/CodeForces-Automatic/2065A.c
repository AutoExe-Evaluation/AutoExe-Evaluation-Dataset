#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases should be in the range [1, 100]

    for (int TC = 1; TC <= TCS; ++TC)
    {
        char s[11]; // max length is 10 + 1 for null terminator
        scanf("%s", s);
        
        assert(strlen(s) <= 10); // PRE: Length of the input string should not exceed 10
        assert(s[strlen(s) - 1] == 's' && s[strlen(s) - 2] == 'u'); // PRE: String should end with "us"

        s[strlen(s) - 2] = '\0'; // remove "us"
        printf("%si\n", s); // append "i"

        assert(strlen(s) + 1 <= 10); // POST: Length of the modified string should still conform to the limit
    }
    
    return 0;
}