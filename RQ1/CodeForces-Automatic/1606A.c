#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases is within bounds
    for (int TC = 1; TC <= TCS; ++TC)
    {
        char s[101];
        scanf("%s", s);
        int len = strlen(s);
        assert(len >= 1 && len <= 100); // PRE: Length of string is within bounds
        int abCount = 0, baCount = 0;

        for (int i = 0; i < len - 1; i++) {
            if (s[i] == 'a' && s[i + 1] == 'b') abCount++;
            if (s[i] == 'b' && s[i + 1] == 'a') baCount++;
        }

        // Making sure the first and last character are the same
        if (s[0] != s[len - 1]) {
            if (s[0] == 'a') s[0] = 'b';
            else s[0] = 'a';
        }

        // Calculate new abCount and baCount
        abCount = 0;
        baCount = 0;
        for (int i = 0; i < len - 1; i++) {
            if (s[i] == 'a' && s[i + 1] == 'b') abCount++;
            if (s[i] == 'b' && s[i + 1] == 'a') baCount++;
        }

        assert(abCount == baCount); // POST: The final counts of AB(s) and BA(s) are equal
        printf("%s\n", s);
    }
    return 0;
}