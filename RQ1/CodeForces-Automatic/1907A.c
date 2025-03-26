#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 64); // PRE: Number of test cases should be between 1 and 64 inclusive
    
    while (TC--) {
        char s[3];
        scanf("%s", s);
        assert(strlen(s) == 2); // PRE: Position string should have exactly 2 characters
        char ch[] = "abcdefgh";
        int it = strchr(ch, s[0]) - ch;
        assert(it >= 0 && it < 8); // PRE: Column character must be from 'a' to 'h'
        assert(s[1] >= '1' && s[1] <= '8'); // PRE: Row character must be from '1' to '8'
        
        for (int i = 0; i < 8; ++i) {
            if (i == it)
                continue;
            else
                printf("%c%c\n", ch[i], s[1]);
        }
        
        for (int i = 1; i <= 8; ++i) {
            if (i == s[1] - '0')
                continue;
            else
                printf("%c%d\n", s[0], i);
        }

        // POST: The output positions are valid rook moves on the chessboard
        assert(TC >= 0); // Ensuring while loop ends correctly
    }
    return 0;
}