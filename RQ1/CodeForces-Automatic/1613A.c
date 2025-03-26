#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--)
    {
        char x[11], y[11];
        int a, b;
        scanf("%s %d %s %d", x, &a, y, &b);
        assert(1 <= atoi(x) && atoi(x) <= 1000000); // PRE: 1 <= x1 <= 10^6
        assert(0 <= a && a <= 1000000); // PRE: 0 <= p1 <= 10^6
        assert(1 <= atoi(y) && atoi(y) <= 1000000); // PRE: 1 <= x2 <= 10^6
        assert(0 <= b && b <= 1000000); // PRE: 0 <= p2 <= 10^6

        int flag = 0;
        if (strlen(x) + a > strlen(y) + b) flag = 1;
        else if (strlen(x) + a < strlen(y) + b) flag = 2;
        else if (strlen(x) + a == strlen(y) + b)
        {
            while (strlen(x) > strlen(y)) strcat(y, "0");
            while (strlen(x) < strlen(y)) strcat(x, "0");
            if (strcmp(x, y) > 0) flag = 1;
            else if (strcmp(x, y) < 0) flag = 2;
        }
        if (flag == 0)
            printf("=\n");
        else if (flag == 1)
            printf(">\n");
        else if (flag == 2)
            printf("<\n");
    }
    // POST: Output correctly indicates the comparison of the two numbers
    return 0;
}