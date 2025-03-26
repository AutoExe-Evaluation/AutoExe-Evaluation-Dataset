#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: 1 <= TCS <= 100
    for (int TC = 1; TC <= TCS; ++TC)
    {
        long long n;
        char s[101];
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100); // PRE: 1 <= n <= 100
        scanf("%s", s);
        
        assert(strlen(s) == n); // PRE: String length matches n
        
        if (n % 3 == 2)
        {
            printf("NO\n");
            continue;
        }
        
        for (int i = 2; i < strlen(s); i += 3)
        {
            if (s[i] != s[i - 1])
            {
                printf("NO\n");
                break;
            }
            if (i == strlen(s) - 1) 
            {
                printf("YES\n");
            }
        }
        if (n % 3 == 0 && strlen(s) % 3 == 0) // POST: Validity check
        {
            printf("YES\n");
        }
    }
    return 0;
}