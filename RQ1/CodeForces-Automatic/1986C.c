#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4

    while (TCS--) 
    {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 100000); // PRE: 1 <= n <= 10^5
        assert(m >= 1 && m <= 100000); // PRE: 1 <= m <= 10^5
        
        char s[100001], c[100001];
        scanf("%s", s);
        assert(strlen(s) == n); // PRE: length of s = n

        int *ind = (int *)malloc(m * sizeof(int));
        for (int i = 0; i < m; ++i) 
        {
            scanf("%d", &ind[i]);
            ind[i]--; // Convert to 0-based index
            assert(ind[i] >= 0 && ind[i] < n); // PRE: 1 <= ind_i <= n
        }

        scanf("%s", c);
        assert(strlen(c) == m); // PRE: length of c = m
        
        // Sort the characters of c
        qsort(c, m, sizeof(char), (int(*)(const void*, const void*))strcmp);
        
        // Prepare to mark the indices
        int *used = (int *)calloc(n, sizeof(int));
        
        for (int i = 0; i < m; ++i) {
            used[ind[i]] = 1;
        }
        
        // index for characters in c
        int j = 0;
        for (int i = 0; i < n; ++i) {
            if (used[i] == 1) {
                s[i] = c[j++];
            }
        }

        printf("%s\n", s);
        free(ind);
        free(used);
        
        assert(strcmp(s, "") != 0); // POST: s is not empty
    }

    return 0;
}