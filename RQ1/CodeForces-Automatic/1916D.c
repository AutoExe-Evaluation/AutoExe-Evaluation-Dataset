#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

void solve(int n)
{
    assert(n % 2 == 1); // PRE: n is an odd number
    char ans[100][100];
    int size = 0;
    
    if(n == 1)
    {
        printf("1\n");
        return;
    }
    
    strcpy(ans[size++], "169");
    strcpy(ans[size++], "196");
    strcpy(ans[size++], "961");

    for(int x = 5; x <= n; x += 2)
    {
        int newSize = size;
        for(int i = 0; i < newSize; i++)
        {
            char s[100] = {};
            sprintf(s, "%s00", ans[i]);
            strcpy(ans[i], s);
        }
        char a[100], b[100], s[100] = {};
        for(int i = 0; i < (x - 3) / 2; ++i)
            strcat(s, "0");
        sprintf(a, "1%s6%s9", s, s);
        sprintf(b, "9%s6%s1", s, s);
        strcpy(ans[size++], a);
        strcpy(ans[size++], b);
    }
    
    for(int i = 0; i < size; i++)
        printf("%s\n", ans[i]);

    assert(size == n); // POST: There are n valid square numbers outputted
}

int main()
{
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases is within bounds
    while (TC--)
    {
        int n;
        scanf("%lld", &n);
        solve(n);
    }
    return 0;
}