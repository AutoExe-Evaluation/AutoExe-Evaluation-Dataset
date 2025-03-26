#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH 7

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4
    while (TC--) 
    {
        char n[MAX_LENGTH];
        scanf("%s", n);
        assert(strlen(n) > 0 && strlen(n) < MAX_LENGTH); // PRE: valid input
        int count = 9 * (strlen(n) - 1) + (n[0] - '0');
        printf("%d\n", count);
        assert(count >= 1 && count <= 999999); // POST: 1 ≤ x ≤ n (n = input)
    }
    return 0;
}