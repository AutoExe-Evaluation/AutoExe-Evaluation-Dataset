#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be in the range [1, 1000]
    
    while (TC--)
    {
        char grid[8][9]; // 8 lines of 8 characters + 1 for null terminator
        for (int i = 0; i < 8; ++i)
        {
            scanf("%s", grid[i]);
            assert(strlen(grid[i]) == 8); // PRE: Each line should contain exactly 8 characters
        }

        char s[9] = ""; // Initialize string to store the result
        for (int j = 0; j < 8; ++j)
        {
            for (int i = 0; i < 8; ++i)
            {
                if (grid[i][j] != '.')
                    strncat(s, &grid[i][j], 1); // Concatenate the character
            }
        }
        
        assert(strlen(s) > 0 && strlen(s) <= 8); // POST: The result should be a non-empty string of length ≤ 8
        printf("%s\n", s);
    }
    return 0;
}