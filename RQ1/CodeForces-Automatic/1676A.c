#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be within valid range.
    
    while (TC--)
    {
        char s[7];
        scanf("%s", s);
        int first_sum = 0, last_sum = 0;

        for (int i = 0; i < 6; ++i)
        {
            assert(s[i] >= '0' && s[i] <= '9'); // PRE: Each character of the string must be a digit.
            if (i < 3)
                first_sum += s[i] - '0';
            else
                last_sum += s[i] - '0';
        }

        if (first_sum == last_sum)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}