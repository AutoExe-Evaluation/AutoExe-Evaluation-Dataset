#include<stdio.h>
#include<assert.h>

int main()
{
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be in the range 1 to 1000

    while (TC--) 
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        assert(a >= 0 && a <= 9); // PRE: Each digit should be in the range 0 to 9
        assert(b >= 0 && b <= 9); // PRE: Each digit should be in the range 0 to 9
        assert(c >= 0 && c <= 9); // PRE: Each digit should be in the range 0 to 9
        
        if(a+b >= 10 || b+c >= 10 || a+c >= 10)
            printf("YES\n");
        else
            printf("NO\n");

        // POST: The output should be "YES" if any two digits sum to 10 or more, otherwise "NO"
    }
    return 0;
}