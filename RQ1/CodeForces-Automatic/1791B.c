#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int t, n, x, y;
    scanf("%d", &t);
    assert(t >= 1 && t <= 1000); // PRE: number of test cases is within valid range
    
    while (t--) 
    {
        x = 0; 
        y = 0;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: length of the string is within valid range
        
        char s[51];
        scanf("%s", s);
        
        for(int i = 0; i < strlen(s); ++i)
        {
            if(s[i] == 'U') y++;
            else if(s[i] == 'D') y--;
            else if(s[i] == 'R') x++;
            else if(s[i] == 'L') x--;
            
            if(x == 1 && y == 1) 
            {
                printf("YES\n");
                break; 
            }
        }

        if(!(x == 1 && y == 1)) 
        {
            printf("NO\n");
        }
    }

    assert(x == 1 && y == 1); // POST: checked conditions for reaching the candy (1,1) after valid moves
    return 0;
}