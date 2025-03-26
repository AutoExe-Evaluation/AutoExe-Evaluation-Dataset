#include<stdio.h>
#include<string.h>
#include<assert.h>

#define MAX_LEN 50

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        int n, m;
        char x[MAX_LEN], s[MAX_LEN];
        scanf("%d %d", &n, &m);
        assert(n * m <= 25); // PRE: 1 <= n * m <= 25
        scanf("%s", x);
        scanf("%s", s);
        
        int ct = 0;
        char temp[MAX_LEN * 10] = {0};
        
        for (int i = 0; i <= 10; ++i) {
            if (strstr(x, s) != NULL) {
                printf("%d\n", i);
                assert(i >= 0 && i <= 10); // POST: 0 <= result <= 10
                break;
            }
            strcat(x, x);
        }
        if (strstr(x, s) == NULL) {
            printf("-1\n");
            assert(strstr(x, s) == NULL); // POST: s is not a substring of x
        }
    }
    return 0;
}