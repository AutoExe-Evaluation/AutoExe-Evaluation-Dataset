#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is within the range

    while (TC--) {
        char s1[4], s2[4], s3[4];
        scanf("%s %s %s", s1, s2, s3);
        assert(strlen(s1) == 3 && strlen(s2) == 3 && strlen(s3) == 3); // PRE: Each row has exactly 3 characters

        if (strcmp(s1, "XXX") == 0) printf("X\n");
        else if (strcmp(s1, "OOO") == 0) printf("O\n");
        else if (strcmp(s1, "+++") == 0) printf("+\n");

        else if (strcmp(s2, "XXX") == 0) printf("X\n");
        else if (strcmp(s2, "OOO") == 0) printf("O\n");
        else if (strcmp(s2, "+++") == 0) printf("+\n");

        else if (strcmp(s3, "XXX") == 0) printf("X\n");
        else if (strcmp(s3, "OOO") == 0) printf("O\n");
        else if (strcmp(s3, "+++") == 0) printf("+\n");

        else if (s1[0] == 'X' && s2[0] == 'X' && s3[0] == 'X') printf("X\n");
        else if (s1[0] == 'O' && s2[0] == 'O' && s3[0] == 'O') printf("O\n");
        else if (s1[0] == '+' && s2[0] == '+' && s3[0] == '+') printf("+\n");

        else if (s1[1] == 'X' && s2[1] == 'X' && s3[1] == 'X') printf("X\n");
        else if (s1[1] == 'O' && s2[1] == 'O' && s3[1] == 'O') printf("O\n");
        else if (s1[1] == '+' && s2[1] == '+' && s3[1] == '+') printf("+\n");

        else if (s1[2] == 'X' && s2[2] == 'X' && s3[2] == 'X') printf("X\n");
        else if (s1[2] == 'O' && s2[2] == 'O' && s3[2] == 'O') printf("O\n");
        else if (s1[2] == '+' && s2[2] == '+' && s3[2] == '+') printf("+\n");

        else if (s1[0] == 'X' && s2[1] == 'X' && s3[2] == 'X') printf("X\n");
        else if (s1[0] == 'O' && s2[1] == 'O' && s3[2] == 'O') printf("O\n");
        else if (s1[0] == '+' && s2[1] == '+' && s3[2] == '+') printf("+\n");

        else if (s1[2] == 'X' && s2[1] == 'X' && s3[0] == 'X') printf("X\n");
        else if (s1[2] == 'O' && s2[1] == 'O' && s3[0] == 'O') printf("O\n");
        else if (s1[2] == '+' && s2[1] == '+' && s3[0] == '+') printf("+\n");

        else printf("DRAW\n");
        
        // POST: Output is valid based on the game state, either one player wins or it's a draw
    }
}